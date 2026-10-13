#include "include/AppLayer.hpp"


AppLayer::AppLayer()
{
	std::print("AppCreated!");
	for (size_t i = 0; i < 10; i++)
	{
		KineticCircle myCircle{ 10.0f,{50.0f * i,10.0f} };


		m_QuadTree.insert(myCircle, myCircle.getCollisionBox());
	}
}

void AppLayer::OnUpdate()
{

	m_Cam.dragAndZoom();

}


void AppLayer::OnRender()
{
	DrawFPS(0,0);

	BeginMode2D(m_Cam.getCam());

	for (auto& circle : m_QuadTree.search(window))
	{
		DrawCircleV(circle->item.getPos(), circle->item.getRadius(), RED);
	}

	EndMode2D();
}
