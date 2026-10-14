#include "include/MenuLayer.hpp"

#include <Application.hpp>

MenuLayer::MenuLayer()
{
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
}

void MenuLayer::OnRender()
{
	
	GuiLabel({ (m_RenderTexSize.x - 400.0f ) / 2.0f,m_RenderTexSize.y*0.1f,400.0f,200.0f }, "Ball_Arena");

	if (GuiButton({ (m_RenderTexSize.x - 400.0f ) / 2.0f, m_RenderTexSize.y * 0.3f,400.0f,100 }, "Play!"))
	{
		
		Application::Get().SwitchLayer<AppLayer>();
		m_ChangeRes = false;
		
	}

	if (GuiButton({ (m_RenderTexSize.x - 400.0f) / 2.0f, m_RenderTexSize.y * 0.5f,400.0f,100.0f }, "Resolution"))
	{
		m_ChangeRes = !m_ChangeRes;
	}


	if (GuiButton({ (m_RenderTexSize.x - 400.0f) / 2.0f, m_RenderTexSize.y * 0.7f,400.0f,100.0f }, "Fullscreen"))
	{
		ToggleFullscreen();
	}

	if (m_ChangeRes)
	{
		changeResolution();
	}

}

bool MenuLayer::OnWindowResize(RenderTextureResize& event)
{
		
	m_RenderTexSize.x = event.GetWidth();
	m_RenderTexSize.y = event.GetHeight();

	std::println("{} : {}", m_RenderTexSize.x, m_RenderTexSize.y);

	return false;
}
