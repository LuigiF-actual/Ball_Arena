#pragma once

#include <array>

#include <RmlUi/Core.h>
#include <RmlUi/Core/Event.h>

struct PendingSettings
{
	int screenWidth = 0;
	int screenHeight = 0;
	int circleResolution = 0;
};

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

class ScreenResolutionBtn : public Rml::EventListener
{
public: 

	ScreenResolutionBtn(Rml::ElementDocument* settingsDoc_,Rml::String& resStr_,int& width_,int& height_)
		:
		m_SettingsDoc(settingsDoc_),
		m_ResTex(resStr_),
		m_Width(width_),
		m_Height(height_)
	{
		m_SettingsDoc->GetElementById("resolution_back")->AddEventListener(Rml::EventId::Click, this);
		m_SettingsDoc->GetElementById("resolution_front")->AddEventListener(Rml::EventId::Click, this);
	}

	void ProcessEvent(Rml::Event& e) override
	{
		const Rml::String& elementId = e.GetCurrentElement()->GetId();

		if (elementId == "resolution_back" && m_ResArrId != 0)
		{
			m_ResTex = pairToString(m_Resolutions[--m_ResArrId]);
			m_Width = m_Resolutions[m_ResArrId].first;
			m_Height = m_Resolutions[m_ResArrId].second;
			m_SettingsDoc->GetContext()->GetDataModel("settings_model").GetModelHandle().DirtyVariable("screenResolution");
		}
		if (elementId == "resolution_front" && m_ResArrId + 1 < m_Resolutions.size())
		{
			m_ResTex = pairToString(m_Resolutions[++m_ResArrId]);
			m_Width = m_Resolutions[m_ResArrId].first;
			m_Height = m_Resolutions[m_ResArrId].second;
			m_SettingsDoc->GetContext()->GetDataModel("settings_model").GetModelHandle().DirtyVariable("screenResolution");
		}
	}

private:

	Rml::String pairToString(std::pair<int, int> res_)
	{
		return { Rml::ToString(res_.first) + " X " + Rml::ToString(res_.second) };
	}

private:	
	int& m_Width;
	int& m_Height;
	size_t m_ResArrId = 0;
	Rml::String& m_ResTex;
	Rml::ElementDocument* m_SettingsDoc = nullptr;
	std::array<std::pair<int, int>, 6> m_Resolutions = { {{1280,720},{1280,1024},{1600,1000},{1600,1200},{1920,1080},{2880,1800}} };
};
