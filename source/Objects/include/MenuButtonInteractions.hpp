#pragma once

#include <RmlUi/Core.h>
#include <RmlUi/Core/Event.h>

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

