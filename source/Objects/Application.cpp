#include <assert.h>
#include <iostream>
#include <ranges>
#include <print>

#include "include/Application.hpp"



static Application* s_Application = nullptr;


Application::Application(const ApplicationSpecification& specification)
	: m_Specification(specification)
{
	s_Application = this;


	if (m_Specification.IsResizeable)
	{
		SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	}
	if (m_Specification.VSync)
	{
		SetConfigFlags(FLAG_VSYNC_HINT);
	}


	InitWindow(m_Specification.Width, m_Specification.Height, m_Specification.Title.c_str());

	m_RenderTarget = LoadRenderTexture(m_Specification.Width, m_Specification.Height);
	SetTextureFilter(m_RenderTarget.texture, TEXTURE_FILTER_POINT);


}

Application::~Application()
{

	CloseWindow();

	s_Application = nullptr;
}

void Application::Run()
{

	// Main Application loop
	while (!WindowShouldClose())
	{
		UpdateDrawFrame();
	}
}

void Application::Stop()
{
	m_Running = false;
}


Application& Application::Get()
{
	assert(s_Application);
	return *s_Application;
}

void Application::UpdateDrawFrame()
{
	for (const std::unique_ptr<Layer>& layer : m_LayerStack)
	{
		layer->OnUpdate();
	}

	BeginTextureMode(m_RenderTarget);

	ClearBackground(RAYWHITE);

	for (const std::unique_ptr<Layer>& layer : m_LayerStack)
	{
		layer->OnRender();
	}

	EndTextureMode();

	BeginDrawing();

	ClearBackground(RAYWHITE);


	DrawTexturePro
	(
		m_RenderTarget.texture,
		Rectangle{ 0, 0, static_cast<float>(m_RenderTarget.texture.width), -static_cast<float>(m_RenderTarget.texture.height) },
		Rectangle{ 0, 0, static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) },
		Vector2{ 0, 0 }, 0.0f, WHITE
	);


	EndDrawing();
}

