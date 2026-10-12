#include "include/AppLayer.hpp"


AppLayer::AppLayer()
{
	std::print("AppCreated!");
}

void AppLayer::OnUpdate()
{

	m_Cam.dragAndZoom();


}


void AppLayer::OnRender()
{
	DrawFPS(0,0);

	BeginMode2D(m_Cam.getCam());

	DrawCircle(100, 100, 30, RED);

	EndMode2D();
}
