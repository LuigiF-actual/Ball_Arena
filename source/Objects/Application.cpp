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

	if (IsKeyPressed(KEY_U))
	{
		UnloadRenderTexture(m_RenderTarget);
		m_RenderTarget = LoadRenderTexture(1920,1080);
	}
	if (IsKeyPressed(KEY_P))
	{
		ToggleFullscreen();
	}

	BeginTextureMode(m_RenderTarget);

	ClearBackground(RAYWHITE);

	for (const std::unique_ptr<Layer>& layer : m_LayerStack)
	{
		layer->OnRender();
	}

	EndTextureMode();

	BeginDrawing();

	ClearBackground(BLACK);

	float scaleX = static_cast<float>(GetScreenWidth()) / m_RenderTarget.texture.width;
	float scaleY = static_cast<float>(GetScreenHeight()) / m_RenderTarget.texture.height;
	float scale = std::min(scaleX, scaleY);
	float width = m_RenderTarget.texture.width * scale;
	float height = m_RenderTarget.texture.height * scale;

	DrawTexturePro
	(
		m_RenderTarget.texture,
		Rectangle{ 0, 0, static_cast<float>(m_RenderTarget.texture.width), -static_cast<float>(m_RenderTarget.texture.height) },
		Rectangle
		{	
			(GetScreenWidth() - width) / 2.0f,
			(GetScreenHeight() - height) / 2.0f,
			width,
			height
		},
		Vector2{ 0, 0 }, 0.0f, WHITE
	);


	EndDrawing();
}

