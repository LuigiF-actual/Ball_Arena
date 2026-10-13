#include "include/AppLayer.hpp"


AppLayer::AppLayer()
{
	std::print("AppCreated!");

	m_QuadTree.resize({ {0.0f,0.0f},{config::worldArea,config::worldArea} });

	auto rand_float = [](const float a, const float b)
		{
			return float(rand()) / float(RAND_MAX) * (b - a) + a;
		};

	for (size_t i = 0; i < config::circleAmmount; i++)
	{
		KineticCircle myCircle{ 
			rand_float(10.0f,50.0f), 
			{rand_float(0.0f,config::worldArea), rand_float(0.0f,config::worldArea)},
			{(unsigned char)(rand() % 256),(unsigned char)(rand() % 256),(unsigned char)(rand() % 256), 255}
		};


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
	
	m_CameraArea = Box{ m_Cam.getCam().target,Vector2{ m_RenderTexSize.x / m_Cam.getCam().zoom, m_RenderTexSize.y / m_Cam.getCam().zoom} };

	BeginMode2D(m_Cam.getCam());

	for (auto& circle : m_QuadTree.search(m_CameraArea))
	{
		//DrawCircleV(circle->item.getPos(), circle->item.getRadius(), RED);
		DrawCircleSector(circle->item.getPos(), circle->item.getRadius(), 0.0f, 360.0f, 10, circle->item.getColor()); // way more perfomant
		circlesDrawn += 1;
	}
	EndMode2D();

	DrawFPS(0,0);
	DrawText(std::to_string(circlesDrawn).c_str(), 100, 10, 32, PURPLE);
}



bool AppLayer::OnWindowResize(RenderTextureResize& event)
{
	std::print("Here!");

	m_RenderTexSize.x = event.GetWidth();
	m_RenderTexSize.y = event.GetHeight();

	event.Handled = true;

	return true;
}
