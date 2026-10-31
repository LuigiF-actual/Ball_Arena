#pragma once

#include "Event.hpp"

#include <format>
#include <functional>

class WindowClosedEvent : public Event
{
public:
	WindowClosedEvent() {};

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


class RenderTextureResize : public Event
{
public:
	RenderTextureResize(int width, int height)
		: m_Width(width), m_Height(height) {}

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }

	std::string ToString() const override
	{
		return std::format("WindowResizeEvent: {}, {}", m_Width, m_Height);
	}

	EVENT_CLASS_TYPE(WindowResize)

private:
	int m_Width, m_Height;
};


class CircleSegments : public Event
{
public:
	CircleSegments(int segments_)
		:
		m_Segments(segments_)
	{}

	int GetSegments() const { return m_Segments; }
	
	EVENT_CLASS_TYPE(CircleSegmentsChange)

private:
	int m_Segments;
};