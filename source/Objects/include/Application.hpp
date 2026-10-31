#pragma once


#include <string>
#include <memory>
#include <vector>
#include <set>
#include <functional>

#include <raylib.h>
#include <raymath.h>

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
	

	void PushLayer(std::unique_ptr<Layer> layer)
	{
		m_LayerStack.push_back(std::move(layer));
	}

	template<typename TLayer>
	requires(std::is_base_of_v<Layer, TLayer>)
	TLayer* GetLayer()
	{
		for (const auto& layer : m_LayerStack)
		{
			TLayer* casted = dynamic_cast<TLayer*>(layer.get());
			if (casted != nullptr)
			{
				return casted;
			}
		}
		return nullptr;
	}


	template<typename T>
	void SwitchLayer()
	{
		T* targetLayer = GetLayer<T>();
		if (targetLayer != nullptr)
		{
			for (std::unique_ptr<Layer>& layer : m_LayerStack)
			{
				layer->SetActive(false);
			}
			targetLayer->SetActive(true);
		}
	}

	void RaiseEvent(Event& event);


	static Application& Get();

	Vector2 GetMouseInRenderTexture()
	{
		const float textureWidth = static_cast<float>(m_RenderTarget.texture.width);

		const float textureHeight = static_cast<float>(m_RenderTarget.texture.height);

		const float scaleX = GetScreenWidth() / textureWidth;
		const float scaleY = GetScreenHeight() / textureHeight;
		const float scale = std::min(scaleX, scaleY);

		const float drawnWidth = textureWidth * scale;
		const float drawnHeight = textureHeight * scale;

		const Vector2 offset{(GetScreenWidth() - drawnWidth) / 2.0f,(GetScreenHeight() - drawnHeight) / 2.0f};

		const Vector2 mouse = GetMousePosition();

		return {
			(mouse.x - offset.x) / scale,
			(mouse.y - offset.y) / scale
		};
	}


	void setResolution(int width, int height);
	
	void setWindowMode(bool isFullScreen)
	{

		if (isFullScreen != IsWindowFullscreen())
		{
			ToggleFullscreen();
		}
	}

private:

	void UpdateDrawFrame();

private:


	ApplicationSpecification m_Specification;

	bool m_Running = true;

	std::vector<std::unique_ptr<Layer>> m_LayerStack;

	RenderTexture2D m_RenderTarget;

	friend class Layer;
};


