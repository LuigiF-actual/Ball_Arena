#pragma once

#include <stdint.h>
#include <vector>
#include <ranges>
#include <print>
#include <array>
#include <string>
#include <memory>

#include <raylib.h>
#include <raymath.h>
#include <RmlUi/Core.h>
#include <RmlUi/Core/Event.h>
#include "RmlUi_Renderer_GL3.h"

#include <GameEvents.hpp>
#include <WorldConfig.hpp>
#include <Application.hpp>
#include <MenuButtonInteractions.hpp>
#include <PendingSettings.hpp>

#include "Layer.hpp"
#include "AppLayer.hpp"



class MenuLayer : public Layer
{
public:
	MenuLayer();
	~MenuLayer();

	void OnEvent(Event& event) override;

	void OnUpdate() override;
	void OnRender() override;


private:

	bool OnWindowResize(RenderTextureResize& event);
	void QueryUserInputs();

	bool SetupDataBinding()
	{
		Rml::DataModelConstructor constructor = m_Context->CreateDataModel("settings_model");
		if (!constructor)
			return false;

		constructor.Bind("screenResolution", &m_PendingSettings.resTex);
		constructor.Bind("circleResolution", &m_PendingSettings.circlePolygons);
		constructor.Bind("windowMode", &m_PendingSettings.fullscreenTex);

		m_SettingsData = constructor.GetModelHandle();

		return true;
	}
	
	void ApplyPendingSettings() 
	{

		CircleSegments event{ m_PendingSettings.circlePolygons };
		Application::Get().RaiseEvent(event);

		Application::Get().setResolution(m_PendingSettings.width, m_PendingSettings.height);
		Application::Get().setWindowMode(m_PendingSettings.fullscreen);
		m_Context->SetDensityIndependentPixelRatio(std::min(GetScreenWidth() / 1600.0f, GetScreenHeight() / 1000.0f));
	}

	void SwitchToGame();

	void ExitGame()
	{
		Application::Get().Stop();
	}

private:
	bool m_ChangeRes = false;

	std::unique_ptr<RenderInterface_GL3> m_Renderer;
	std::unique_ptr<SwitchDoc> m_SwitchDoc;
	std::unique_ptr<ScreenResolutionBtn> m_ScreenResBtn;
	std::unique_ptr<CircleSegmentsBtn> m_CircleResBtn;
	std::unique_ptr<FullScreenBtn> m_FullScreenBtn;
	std::unique_ptr<ApplyBtn> m_ApplyBtn;
	std::unique_ptr<PlayGameBtn> m_PlayGameBtn;
	std::unique_ptr<ExitGameBtn> m_ExitGameBtn;

	Rml::DataModelHandle m_SettingsData;
	Rml::Context* m_Context{nullptr};
	Rml::ElementDocument* m_MainMenuDoc{ nullptr };
	Rml::ElementDocument* m_SettingsDoc{nullptr};

	Vector2 m_RenderTexSize{ config::initialResX, config::initialResY };
	PendingSettings m_PendingSettings;

};
