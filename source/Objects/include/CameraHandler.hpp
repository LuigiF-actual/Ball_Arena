#pragma once

#include <raylib.h>
#include <raymath.h>

class CameraHandler
{
public:
	CameraHandler() = default;
	~CameraHandler() = default;

	void dragAndZoom()
	{

		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Vector2 delta = GetMouseDelta();
			delta = Vector2Scale(delta, -1.0f / m_Cam.zoom);
			m_Cam.target = Vector2Add(m_Cam.target, delta);
		}


        float wheel = GetMouseWheelMove();
		if (wheel != 0)
		{
			float scale = 0.2f * wheel;
			m_Cam.zoom = Clamp(expf(logf(m_Cam.zoom) + scale), 0.125f, 64.0f);
		}
	}

	const Camera2D& getCam()
	{
		return m_Cam;
	}

private:
	Camera2D m_Cam{ {0.0f,0.0f}, {0.0f,0.0f}, 0.0f, 1.0f };
};
