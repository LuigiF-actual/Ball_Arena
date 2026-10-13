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

void AppLayer::OnEvent(Event& event)
{
	std::println("{}", event.ToString());

	EventDispatcher dispatcher(event);

	dispatcher.Dispatch<RenderTextureResize>(
		[this]
		(RenderTextureResize& e)
		{
			return OnWindowResize(e);
		}
	);

}

void AppLayer::OnUpdate()
{

	m_Cam.dragAndZoom();

}


void AppLayer::OnRender()
{
	int circlesDrawn = 0;
	

	BeginMode2D(m_Cam.getCam());

	for (auto& circle : m_QuadTree.search(cameraArea))
	{
		DrawCircleV(circle->item.getPos(), circle->item.getRadius(), RED);
		circlesDrawn += 1;
	}

	EndMode2D();

	DrawFPS(0,0);
	DrawText(std::to_string(circlesDrawn).c_str(), 100, 10, 32, PURPLE);
}



bool AppLayer::OnWindowResize(RenderTextureResize& event)
{
	std::print("Here!");

	cameraArea.Body.width = event.GetWidth();
	cameraArea.Body.height = event.GetWidth();

	event.Handled = true;

	return true;
}
