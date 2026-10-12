#pragma once

#include <array>
#include <vector>
#include <cmath>
#include <memory>
#include <string>
#include <chrono>
#include <list>
#include <iterator>
#include <iostream>
#include <print>

#include <raylib.h>
#include <raymath.h>

#include "Box.hpp"
#include "WorldConfig.hpp"


constexpr size_t MAX_DEPTH = 8;
//constexpr float fArea = 50'000.0f;
//constexpr float world_friction = 0.97f;
//float fSearchSize = 10.0f;


template<typename T>
struct QuadTreeItemLocation
{
	typename std::list< std::pair<Box, T> >* container;
	typename std::list< std::pair<Box, T> >::iterator iterator;
};


template <typename OBJECT_TYPE>
class DynamicQuadTree
{
public:
	DynamicQuadTree(const Box& size = { {0.0f,0.0f},{100.0f,100.0f} }, const size_t nDepth = 0)
	{
		m_depth = nDepth;
		resize(size);

	}

	void resize(const Box& rArea)
	{
		clear();
		m_rect = rArea;
		Vector2 vChildSize = Vector2Divide(m_rect.getSize(), { 2.0f,2.0f });

		m_rChild =
		{
			Box(m_rect.getTopLeft(),vChildSize),
			Box({m_rect.Body.x + vChildSize.x, m_rect.Body.y},vChildSize),
			Box({m_rect.Body.x,m_rect.Body.y + vChildSize.y},vChildSize),
			Box({Vector2Add(m_rect.getTopLeft(),vChildSize)},vChildSize)
		};
	}

	void clear()
	{
		m_pItems.clear();

		for (int i = 0; i < 4; i++)
		{
			if (m_pChild[i] != nullptr)
			{
				m_pChild[i]->clear();
			}
			m_pChild[i].reset();
		}

	}

	size_t size() const
	{
		size_t nCount = m_pItems.size();
		for (int i = 0; i < 4; i++)
		{
			if (m_pChild[i] != nullptr)
			{
				nCount += m_pChild[i]->size();
			}
			return nCount;
		}
	}

	QuadTreeItemLocation<OBJECT_TYPE> insert(const OBJECT_TYPE& item, const Box& itemSize)
	{
		for (int i = 0; i < 4; i++)
		{
			if (m_rChild[i].contains(itemSize))
			{

				if (m_depth + 1 < MAX_DEPTH)
				{

					if (!m_pChild[i])
					{
						m_pChild[i] = std::make_shared<DynamicQuadTree<OBJECT_TYPE>>(m_rChild[i], m_depth + 1);
					}

					return m_pChild[i]->insert(item, itemSize);
				}

			}

		}

		m_pItems.push_back({ itemSize,item });
		return { &m_pItems, std::prev(m_pItems.end()) };
	}


	std::list<OBJECT_TYPE> search(const Box& rArea) const
	{
		std::list<OBJECT_TYPE> listItems;
		search(rArea, listItems);
		return listItems;
	}

	void search(const Box& rArea, std::list<OBJECT_TYPE>& listItems) const
	{
		for (const auto& p : m_pItems)
		{
			if (rArea.overlap(p.first))
			{
				listItems.push_back(p.second);
			}

		}

		for (int i = 0; i < 4; i++)
		{
			if (m_pChild[i] != nullptr)
			{
				if (rArea.contains(m_rChild[i]))
				{
					m_pChild[i]->items(listItems);
				}
				else if (m_rChild[i].overlap(rArea))
				{
					m_pChild[i]->search(rArea, listItems);
				}
			}
		}
	}

	void items(std::list<OBJECT_TYPE>& listItems) const
	{
		for (const auto& p : m_pItems)
		{
			listItems.push_back(p.second);
		}

		for (int i = 0; i < 4; i++)
		{
			if (m_pChild[i] != nullptr)
			{
				m_pChild[i]->items(listItems);
			}
		}
	}


	const Box& area()
	{
		return m_rect;
	}

	bool remove(OBJECT_TYPE pItem)
	{
		auto it = std::find_if(m_pItems.begin(), m_pItems.end(),
			[&pItem](const std::pair<Box, OBJECT_TYPE>& a)
			{
				return a.second == pItem;
			});

		if (it != m_pItems.end())
		{
			m_pItems.erase(it);
			return true;
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if (m_pChild[i])
				{
					if (m_pChild[i]->remove(pItem))
					{
						return true;
					}
				}
			}
		}

		return false;
	}

	void DrawQuads()
	{
		for (auto& i : m_rChild)
		{
			DrawRectangleLinesEx(i.Body, 10.0f, PINK);
		}

		for (int i = 0; i < 4; i++)
		{
			if (m_pChild[i] != nullptr)
			{
				m_pChild[i]->DrawQuads();
			}
		}
	}

protected:

	size_t m_depth = 0;

	Box m_rect;

	// 4 child areas of the quadtree
	std::array<Box, 4> m_rChild{};

	// 4 potential children of the staticquadtree
	std::array<std::shared_ptr<DynamicQuadTree<OBJECT_TYPE>>, 4> m_pChild{};

	std::list<std::pair<Box, OBJECT_TYPE>> m_pItems;


};




template<typename T>
struct QuadTreeItem
{
	// The item Itself
	T item;



	// A "locator" to the container/iterator that points to this item's iterator in the
	// top level list - phew
	QuadTreeItemLocation<typename std::list<QuadTreeItem<T>>::iterator > pItem;

	KinectBody forces{ item, (item.Body.width * item.Body.height) };
};

// (float(rand()) / float(RAND_MAX) * (100.0f - 10.0f) + 10.0f) 

template<typename OBJECT_TYPE>
class DynamicQuadTreeContainer
{


	using QuadTreeContainer = std::list<QuadTreeItem<OBJECT_TYPE>>;
public:

	using iterator = typename QuadTreeContainer::iterator;

	QuadTreeContainer m_allItems;
	DynamicQuadTree<typename QuadTreeContainer::iterator> root;

public:
	DynamicQuadTreeContainer(const Box& size = { {0.0f,0.0f},{100.0f,100.0f} }, const size_t nDepth = 0)
		:
		root(size, nDepth)
	{
		std::print("Here in container");
	}

	~DynamicQuadTreeContainer() = default;

	void resize(const Box& rArea)
	{
		root.resize(rArea);
	}

	size_t size() const
	{
		return m_allItems.size();
	}

	bool empty() const
	{
		return m_allItems.empty();
	}

	void clear()
	{
		root.clear();
		m_allItems.clear();
	}

	typename QuadTreeContainer::iterator begin()
	{
		return m_allItems.begin();
	}

	typename QuadTreeContainer::iterator end()
	{
		return m_allItems.end();
	}

	typename QuadTreeContainer::iterator cbegin()
	{
		return m_allItems.cbegin();
	}

	typename QuadTreeContainer::iterator cend()
	{
		return m_allItems.cend();
	}

	void insert(const OBJECT_TYPE& item, const Box& itemsize)
	{
		QuadTreeItem<OBJECT_TYPE> newItem;
		newItem.item = item;

		m_allItems.push_back(newItem);


		m_allItems.back().pItem = root.insert(std::prev(m_allItems.end()), itemsize);
	}

	std::list<typename QuadTreeContainer::iterator> search(const Box& rArea) const
	{
		std::list<typename QuadTreeContainer::iterator> listItemPointers;
		root.search(rArea, listItemPointers);
		return listItemPointers;
	}

	void remove(typename QuadTreeContainer::iterator& item)
	{
		// Iterator points to a QuadTreeItem
		item->pItem.container->erase(item->pItem.iterator);

		m_allItems.erase(item);
	}

	void drawQuads()
	{
		root.DrawQuads();
	}

	void relocate(typename QuadTreeContainer::iterator& item, const Box& itemsize)
	{
		item->pItem.container->erase(item->pItem.iterator);

		item->pItem = root.insert(item, itemsize);
	}


private:

};