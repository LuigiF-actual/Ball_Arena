#pragma once

#include <string>
#include <functional>

enum class EventType
{
	None = 0,
	WindowClose, WindowResize,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
							virtual EventType GetEventType() const override { return GetStaticType(); }\
							virtual const char* GetName() const override { return #type; }

class Event
{
public:
	bool Handled = false;

	virtual ~Event() {}
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual std::string ToString() const { return GetName(); }

};

class EventDispatcher
{
public:
	EventDispatcher(Event& event)
		: m_Event(event) {}

	template<typename T_Event>
	bool Dispatch(std::function<bool(T_Event&)> func)
	{
		if (m_Event.GetEventType() == T_Event::GetStaticType() && !m_Event.Handled)
		{
			m_Event.Handled = func(static_cast<T_Event&>(m_Event));
			return true;
		}
		return false;
	}
private:
	Event& m_Event;
};

class WindowClosedEvent : public Event
{
public:
	WindowClosedEvent() {}

	EVENT_CLASS_TYPE(WindowClose)
};

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height) {}

	uint32_t GetWidth() const { return m_Width; }
	uint32_t GetHeight() const { return m_Height; }

	std::string ToString() const override
	{
		return std::format("WindowResizeEvent: {}, {}", m_Width, m_Height);
	}

	EVENT_CLASS_TYPE(WindowResize)
private:
	uint32_t m_Width, m_Height;
};
