#pragma once

#include <string>
#include <functional>

enum class EventType
{
	None = 0,
	WindowClose, WindowResize,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
	CircleSegmentsChange
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

