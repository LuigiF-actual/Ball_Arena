#include "include/MenuLayer.hpp"

#include <Application.hpp>
#include <rlgl.h>

MenuLayer::MenuLayer()
{

	RmlGL3::Initialize();

	m_Renderer = std::make_unique<RenderInterface_GL3>();
	Rml::SetRenderInterface(m_Renderer.get());

	Rml::Initialise();

	m_Context = Rml::CreateContext(
		"main",
		Rml::Vector2i{ GetScreenWidth(), GetScreenHeight() }
	);

	if (!Rml::LoadFontFace("Assets/fonts/Acme 9 Regular.ttf"))
	{
		TraceLog(LOG_ERROR, "FONT NOT LOADED!");
	}

	SetupDataBinding();

	m_MainMenuDoc = m_Context->LoadDocument("Assets/ui/main.rml");
	m_SettingsDoc = m_Context->LoadDocument("Assets/ui/settings.rml");

	if (m_MainMenuDoc)
	{
		m_MainMenuDoc->Show();
	}
	else
	{
		TraceLog(LOG_ERROR, "Main menu not available");
	}

	m_SwitchDoc = std::make_unique<SwitchDoc>(m_MainMenuDoc, m_SettingsDoc);
	m_ScreenResBtn = std::make_unique<ScreenResolutionBtn>(m_SettingsDoc, m_PendingSettings);
	m_CircleResBtn = std::make_unique<CircleSegmentsBtn>(m_SettingsDoc,m_PendingSettings);
	m_FullScreenBtn = std::make_unique<FullScreenBtn>(m_SettingsDoc, m_PendingSettings);
	m_ApplyBtn = std::make_unique<ApplyBtn>(m_SettingsDoc, [this] { ApplyPendingSettings(); });
	m_PlayGameBtn = std::make_unique<PlayGameBtn>(m_MainMenuDoc, [this] { SwitchToGame(); });
	m_ExitGameBtn = std::make_unique<ExitGameBtn>(m_MainMenuDoc, [this] { ExitGame(); });


	m_Context->SetDensityIndependentPixelRatio(std::min(GetScreenWidth() / 1600.0f, GetScreenHeight() / 1000.0f));
}

MenuLayer::~MenuLayer()
{
	Rml::Shutdown();
	RmlGL3::Shutdown();
}


void MenuLayer::OnEvent(Event& event)
{
	
	EventDispatcher dispatcher(event);

	dispatcher.Dispatch<RenderTextureResize>(
		[this]
		(RenderTextureResize& e)
		{
			return OnWindowResize(e);
		}
	);

}

void MenuLayer::OnUpdate()
{

	m_Context->SetDimensions(Rml::Vector2i{ GetScreenWidth(), GetScreenHeight() });

	QueryUserInputs();

	m_Context->Update();

}

void MenuLayer::OnRender()
{
	m_Renderer->SetViewport(GetScreenWidth(), GetScreenHeight());
	rlDrawRenderBatchActive();
	m_Renderer->BeginFrame();

	m_Context->Render();

	m_Renderer->EndFrame();
}

bool MenuLayer::OnWindowResize(RenderTextureResize& event)
{
		
	m_RenderTexSize.x = event.GetWidth();
	m_RenderTexSize.y = event.GetHeight();

	std::println("{} : {}", m_RenderTexSize.x, m_RenderTexSize.y);

	return false;
}

void MenuLayer::QueryUserInputs()
{
	
	const Vector2 mouse = GetMousePosition();

	m_Context->ProcessMouseMove(
		static_cast<int>(mouse.x),
		static_cast<int>(mouse.y),
		0
	);

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		m_Context->ProcessMouseButtonDown(0, 0);
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		m_Context->ProcessMouseButtonUp(0, 0);
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		m_Context->ProcessMouseButtonDown(1, 0);
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
	{
		m_Context->ProcessMouseButtonUp(1, 0);
	}

	const float wheel = GetMouseWheelMove();
	if (wheel != 0.0f)
	{
		m_Context->ProcessMouseWheel(-wheel, 0);
	}

}

void MenuLayer::SwitchToGame()
{
	Application::Get().SwitchLayer<AppLayer>();
}
