#pragma once


#include <stdint.h>
#include <vector>
#include <ranges>
#include <print>

#include <raylib.h>


#include "Layer.hpp"

#include <CameraHandler.hpp>
#include <KineticCircle.hpp>
#include <QuadTree.hpp>
#include <Box.hpp>

class AppLayer : public Layer
{
public:
	AppLayer();
	~AppLayer() = default;

	void OnUpdate() override;
	void OnRender() override;

private:

	CameraHandler m_Cam;
	Box window{ 0.0f,0.0f,720.0f,720.0f };

	DynamicQuadTreeContainer<KineticCircle> m_QuadTree;

	KineticCircle m_Cir{ 45.0f,{200.0f,200.0f} };

};
