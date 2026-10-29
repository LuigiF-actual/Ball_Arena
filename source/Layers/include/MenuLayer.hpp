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

#include <WindowEvents.hpp>
#include <WorldConfig.hpp>
#include <Application.hpp>
#include <MenuButtonInteractions.hpp>

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

private:
	bool m_ChangeRes = false;

	Vector2 m_RenderTexSize{ config::initialResX, config::initialResY };
	std::unique_ptr<RenderInterface_GL3> m_Renderer;
	std::unique_ptr<SwitchDoc> m_SwitchDoc;

	Rml::DataModelHandle m_SettingsData;
	Rml::Context* m_Context{nullptr};
	Rml::ElementDocument* m_MainMenuDoc{ nullptr };
	Rml::ElementDocument* m_SettingsDoc{nullptr};
};
