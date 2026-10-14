#pragma once

#include <stdint.h>
#include <vector>
#include <ranges>
#include <print>
#include <array>
#include <string>

#include <raylib.h>
#include <raymath.h>
#include <raygui.h>



#include <WindowEvents.hpp>
#include <WorldConfig.hpp>
#include <Application.hpp>

#include "Layer.hpp"
#include "AppLayer.hpp"



class MenuLayer : public Layer
{
public:
	MenuLayer();
	~MenuLayer() = default;

	void OnEvent(Event& event) override;

	void OnUpdate() override;
	void OnRender() override;


private:

	bool OnWindowResize(RenderTextureResize& event);

	void changeResolution()
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (GuiButton({ 0.0f, (m_RenderTexSize.y * 0.2f) * i, m_RenderTexSize.x*0.3f, 100.0f },
				(std::to_string((int)m_Resolutions[i].x) + " : " + std::to_string((int)m_Resolutions[i].y)).c_str()
			))
			{
				Application::Get().setResolution((int)m_Resolutions[i].x, (int)m_Resolutions[i].y);
			}
		}
	}

private:
	bool m_ChangeRes = false;

	Vector2 m_RenderTexSize{ config::initialResX, config::initialResY };

	std::array<Vector2, 4> m_Resolutions{ Vector2{1920,1080}, Vector2{1600,1200}, Vector2{1280,800}, Vector2{1024,768} };

};
