#pragma once


#include <string>
#include <memory>
#include <vector>
#include <set>
#include <functional>

#include <raylib.h>

#include <Layer.hpp>

#include "Event.hpp"

struct ApplicationSpecification
{
	std::string Name = "Application";
	std::string Title;
	uint32_t Width = 1280;
	uint32_t Height = 720;
	bool IsResizeable = true;
	bool VSync = true;

	using EventCallbackFn = std::function<void(Event&)>;
	EventCallbackFn EventCallback;
};

class Application
{
public:
	Application(const ApplicationSpecification& specification = ApplicationSpecification());
	~Application();

	void Run();
	void Stop();
	

	template<typename TLayer>
	requires(std::is_base_of_v<Layer, TLayer>)
	void PushLayer()
	{
		m_LayerStack.push_back(std::make_unique<TLayer>());
	}

	template<typename TLayer>
	requires(std::is_base_of_v<Layer, TLayer>)
	TLayer* GetLayer()
	{
		for (const auto& layer : m_LayerStack)
		{
			if (auto casted = dynamic_cast<TLayer*>(layer.get()))
				return casted;
		}
		return nullptr;
	}

	void RaiseEvent(Event& event);


	static Application& Get();

private:

	void UpdateDrawFrame();

private:


	ApplicationSpecification m_Specification;

	bool m_Running = false;

	std::vector<std::unique_ptr<Layer>> m_LayerStack;

	RenderTexture2D m_RenderTarget;

	friend class Layer;
};


