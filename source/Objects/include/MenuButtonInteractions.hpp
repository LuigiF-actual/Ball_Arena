#pragma once

#include <array>

#include <RmlUi/Core.h>
#include <RmlUi/Core/Event.h>

#include "PendingSettings.hpp"


class SwitchDoc : public Rml::EventListener
{
public:
	SwitchDoc(Rml::ElementDocument* menuDoc_, Rml::ElementDocument* settingsDoc_)
		:
		m_MenuDoc(menuDoc_),
		m_SettingsDoc(settingsDoc_)
	{
		m_MenuDoc->GetElementById("settings_btn")->AddEventListener(Rml::EventId::Click, this);
		m_SettingsDoc->GetElementById("back_btn")->AddEventListener(Rml::EventId::Click, this);
	}
	~SwitchDoc() = default;

	void ProcessEvent(Rml::Event& e) override
	{
		const Rml::String& elementId = e.GetCurrentElement()->GetId();

		if (elementId == "settings_btn")
		{
			m_MenuDoc->Hide();
			m_SettingsDoc->Show();
		}
		if (elementId == "back_btn")
		{
			m_SettingsDoc->Hide();
			m_MenuDoc->Show();
		}

	}

private:

	Rml::ElementDocument* m_MenuDoc;
	Rml::ElementDocument* m_SettingsDoc;
};

class FullScreenBtn : public Rml::EventListener
{
public:
	FullScreenBtn(Rml::ElementDocument* settingsDoc_, PendingSettings& settings_)
		:
		m_SettingsDoc(settingsDoc_),
		m_PendingSettings(settings_)
	{
		m_SettingsDoc->GetElementById("window_mode")->AddEventListener(Rml::EventId::Click, this);
	}

	void ProcessEvent(Rml::Event& e) override
	{
		const Rml::String& elementId = e.GetCurrentElement()->GetId();
		if (m_PendingSettings.fullscreen)
		{
			m_PendingSettings.fullscreenTex = "Windowed";
			m_PendingSettings.fullscreen = false;
		}
		else if(!m_PendingSettings.fullscreen)
		{
			m_PendingSettings.fullscreenTex = "Fullscreen";
			m_PendingSettings.fullscreen = true;
		}
		m_SettingsDoc->GetContext()->GetDataModel("settings_model").GetModelHandle().DirtyVariable("windowMode");

	}

private:
	PendingSettings& m_PendingSettings;
	Rml::ElementDocument* m_SettingsDoc = nullptr;
};

class ScreenResolutionBtn : public Rml::EventListener
{
public: 

	ScreenResolutionBtn(Rml::ElementDocument* settingsDoc_,PendingSettings& settings_)
		:
		m_SettingsDoc(settingsDoc_),
		m_PendingSettings(settings_)
	{
		m_SettingsDoc->GetElementById("resolution_back")->AddEventListener(Rml::EventId::Click, this);
		m_SettingsDoc->GetElementById("resolution_front")->AddEventListener(Rml::EventId::Click, this);
	}

	void ProcessEvent(Rml::Event& e) override
	{
		const Rml::String& elementId = e.GetCurrentElement()->GetId();

		if (elementId == "resolution_back" && m_ResArrId != 0)
		{
			m_PendingSettings.resTex = pairToString(m_Resolutions[--m_ResArrId]);
			m_PendingSettings.width = m_Resolutions[m_ResArrId].first;
			m_PendingSettings.height = m_Resolutions[m_ResArrId].second;
			m_SettingsDoc->GetContext()->GetDataModel("settings_model").GetModelHandle().DirtyVariable("screenResolution");
		}
		else if (elementId == "resolution_front" && m_ResArrId + 1 < m_Resolutions.size())
		{
			m_PendingSettings.resTex = pairToString(m_Resolutions[++m_ResArrId]);
			m_PendingSettings.width = m_Resolutions[m_ResArrId].first;
			m_PendingSettings.height = m_Resolutions[m_ResArrId].second;
			m_SettingsDoc->GetContext()->GetDataModel("settings_model").GetModelHandle().DirtyVariable("screenResolution");
		}
	}

private:

	Rml::String pairToString(std::pair<int, int> res_)
	{
		return { Rml::ToString(res_.first) + " X " + Rml::ToString(res_.second) };
	}

private:	
	PendingSettings& m_PendingSettings;
	size_t m_ResArrId = 0;
	Rml::ElementDocument* m_SettingsDoc = nullptr;
	std::array<std::pair<int, int>, 6> m_Resolutions = { {{1280,720},{1280,1024},{1600,1000},{1600,1200},{1920,1080},{2880,1800}} };
};



class CircleSegmentsBtn : public Rml::EventListener
{
public:

	CircleSegmentsBtn(Rml::ElementDocument* settingsDoc_, PendingSettings& settings_)
		:
		m_SettingsDoc(settingsDoc_),
		m_PendingSettings(settings_)
	{
		m_SettingsDoc->GetElementById("circle_back")->AddEventListener(Rml::EventId::Click, this);
		m_SettingsDoc->GetElementById("circle_front")->AddEventListener(Rml::EventId::Click, this);
	}

	void ProcessEvent(Rml::Event& e) override
	{
		const Rml::String& elementId = e.GetCurrentElement()->GetId();

		if (elementId == "circle_back" && m_ResArrId != 0)
		{
			--m_ResArrId;
			m_PendingSettings.resTex = Rml::ToString(m_Resolutions[m_ResArrId]);
			m_PendingSettings.circlePolygons = m_Resolutions[m_ResArrId];
			m_SettingsDoc->GetContext()->GetDataModel("settings_model").GetModelHandle().DirtyVariable("circleResolution");
		}
		else if (elementId == "circle_front" && m_ResArrId + 1 < m_Resolutions.size())
		{
			++m_ResArrId;
			m_PendingSettings.resTex = Rml::ToString(m_Resolutions[m_ResArrId]);
			m_PendingSettings.circlePolygons = m_Resolutions[m_ResArrId];
			m_SettingsDoc->GetContext()->GetDataModel("settings_model").GetModelHandle().DirtyVariable("circleResolution");
		}
	}

private:
	PendingSettings& m_PendingSettings;
	size_t m_ResArrId = 0;
	Rml::ElementDocument* m_SettingsDoc = nullptr;
	std::array<int, 6> m_Resolutions = {6,12,24,36,48,62};
};


class ApplyBtn : public Rml::EventListener
{
public:
	ApplyBtn(Rml::ElementDocument* settingsDoc_, std::function<void()> applySettings_)
		:
		m_SettingsDoc(settingsDoc_),
		m_ApplySettings(applySettings_)
	{
		m_SettingsDoc->GetElementById("apply_btn")->AddEventListener(Rml::EventId::Click, this);
	}

	void ProcessEvent(Rml::Event& e) override
	{
		m_ApplySettings();
	}

private:
	Rml::ElementDocument* m_SettingsDoc = nullptr;
	std::function<void()> m_ApplySettings;
};


class PlayGameBtn : public Rml::EventListener
{
public:
	PlayGameBtn(Rml::ElementDocument* mainDoc_, std::function<void()> applySettings_)
		:
		m_MainDoc(mainDoc_),
		m_PlayGame(applySettings_)
	{
		m_MainDoc->GetElementById("play_btn")->AddEventListener(Rml::EventId::Click, this);
	}

	void ProcessEvent(Rml::Event& e) override
	{
		m_PlayGame();
	}

private:
	Rml::ElementDocument* m_MainDoc = nullptr;
	std::function<void()> m_PlayGame;
};

class ExitGameBtn : public Rml::EventListener
{
public:
	ExitGameBtn(Rml::ElementDocument* mainDoc_, std::function<void()> applySettings_)
		:
		m_MainDoc(mainDoc_),
		m_ExitGame(applySettings_)
	{
		m_MainDoc->GetElementById("exit_btn")->AddEventListener(Rml::EventId::Click, this);
	}

	void ProcessEvent(Rml::Event& e) override
	{
		m_ExitGame();
	}

private:
	Rml::ElementDocument* m_MainDoc = nullptr;
	std::function<void()> m_ExitGame;
};