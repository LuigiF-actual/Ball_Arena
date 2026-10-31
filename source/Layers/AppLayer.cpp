#include "include/AppLayer.hpp"

#include <Application.hpp>

AppLayer::AppLayer()
{
	std::print("AppCreated!");

	m_ActiveHandler = m_QuadTree.end();

	m_QuadTree.resize({ {0.0f,0.0f},{config::worldArea,config::worldArea} });

	auto rand_float = [](const float a, const float b)
		{
			return float(rand()) / float(RAND_MAX) * (b - a) + a;
		};

	for (size_t i = 0; i < config::circleAmmount; i++)
	{
		KineticCircle myCircle{ 
			rand_float(config::minCircleRadius,config::maxCircleRadius), 
			{rand_float(0.0f,config::worldArea), rand_float(0.0f,config::worldArea)},
			{(unsigned char)(rand() % 256),(unsigned char)(rand() % 256),(unsigned char)(rand() % 256), 255}
		};


		m_QuadTree.insert(myCircle, myCircle.getCollisionBox());
	}
}

void AppLayer::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);

	dispatcher.Dispatch<RenderTextureResize>(
		[this]
		(RenderTextureResize& e)
		{
			return OnWindowResize(e);
		}
	);

	dispatcher.Dispatch<CircleSegments>(
		[this]
		(CircleSegments& e)
		{
			return OnCircleSegmentsChange(e);
		}
	);

}

void AppLayer::OnUpdate()
{
	checkForLayerSwitching();

	m_Cam.dragAndZoom();

	updateMousePos();

	checkForClicks();
	updateMouseDrag();

	updatePhysics();

	m_CameraArea = Box{ m_Cam.getCam().target,Vector2{ m_RenderTexSize.x / m_Cam.getCam().zoom, m_RenderTexSize.y / m_Cam.getCam().zoom} };
}


void AppLayer::OnRender()
{
	int circlesDrawn = 0;
	

	BeginMode2D(m_Cam.getCam());

	for (auto& circle : m_QuadTree.search(m_CameraArea))
	{
		DrawCircleSector(circle->item.getPos(), circle->item.getRadius(), 0.0f, 360.0f, m_CircleSegments, circle->item.getColor()); // way more perfomant
		circlesDrawn += 1;
	}

	DrawRectangleRec(m_ClickArea.Body, BLACK);

	if (m_IsDragging && (m_ActiveHandler != m_QuadTree.end()))
	{
		DrawLineV(m_WorldMousePos, m_ActiveHandler->item.getPos(), PINK);
	}

	EndMode2D();

	DrawFPS(0,0);
	DrawText(("Objects in Screen:" + std::to_string(circlesDrawn)).c_str(), 100, 0, 32, PURPLE);
	DrawText(( "Active Objs: " + std::to_string(m_ActiveObjs.size())).c_str(), 500, 0, 32, PURPLE);
}



bool AppLayer::OnWindowResize(RenderTextureResize& event)
{

	m_RenderTexSize.x = event.GetWidth();
	m_RenderTexSize.y = event.GetHeight();


	return false;
}

bool AppLayer::OnCircleSegmentsChange(CircleSegments& event)
{
	m_CircleSegments = event.GetSegments();
	return true;
}


void AppLayer::updateMousePos()
{
	float scaleX = static_cast<float>(GetScreenWidth()) / m_RenderTexSize.x;
	float scaleY = static_cast<float>(GetScreenHeight()) / m_RenderTexSize.y;
	float scale = std::min(scaleX, scaleY);

	float drawnWidth = m_RenderTexSize.x * scale;
	float drawnHeight = m_RenderTexSize.y * scale;

	Vector2 textureOffset{
		(GetScreenWidth() - drawnWidth) / 2.0f,
		(GetScreenHeight() - drawnHeight) / 2.0f
	};

	Vector2 mouse = GetMousePosition();

	Vector2 mouseInRenderTexture{
		(mouse.x - textureOffset.x) / scale,
		(mouse.y - textureOffset.y) / scale
	};

	m_WorldMousePos = GetScreenToWorld2D(mouseInRenderTexture, m_Cam.getCam());
}

void AppLayer::checkForClicks()
{
	m_ClickArea.Body.x = m_WorldMousePos.x - m_ClickArea.Body.width / 2.0f;
	m_ClickArea.Body.y = m_WorldMousePos.y - m_ClickArea.Body.height / 2.0f;


	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{

		auto listOfCircles = m_QuadTree.search(m_ClickArea);

		if (listOfCircles.empty() != true)
		{
			m_ActiveHandler = *listOfCircles.begin();
			m_IsDragging = true;
		}
		
	}

}


void AppLayer::updateMouseDrag()
{

	if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && m_IsDragging)
	{
		m_IsDragging = false;


		launchCircle(m_ActiveHandler->item);


		m_ActiveObjs.push_back(m_ActiveHandler);
		m_ActiveHandler = m_QuadTree.end();
	}

}


void AppLayer::launchCircle(KineticCircle& circle_)
{
	auto& body = circle_.getForces();

	Vector2 pull = Vector2Subtract(circle_.getPos(), m_WorldMousePos);
	float pullLength = Vector2Length(pull);
	pullLength = Clamp(pullLength, 1.0f, 1000.0f);


	if (pullLength <= 0.0f)
	{
		return;
	}

	body.direction = Vector2Normalize(Vector2Scale(pull, 1.0f / pullLength));

	body.velocity = Vector2Scale(body.direction, pullLength * config::launchMultiplier);

	body.isMoving = true;
}

void AppLayer::updatePhysics()
{

	for (auto activeIt = m_ActiveObjs.begin(); activeIt != m_ActiveObjs.end();)
	{
		auto circle = *activeIt;

		circle->item.getForces().move(circle->item.getPosition());

		if (circle->item.getForces().speed <= 0.1f)
		{
			circle->item.getForces().isMoving = false;
			activeIt = m_ActiveObjs.erase(activeIt);
			continue;
		}


		auto possibleColliders = m_QuadTree.search(circle->item.getCollisionBox());

		for (auto& canditate : possibleColliders)
		{
			if ((canditate == circle))
			{
				continue;
			}

			if ((!circle->item.overlap(canditate->item)))
			{
				continue;
			}




			transferVelocity(circle->item, canditate->item);


			m_QuadTree.relocate(canditate, canditate->item.getCollisionBox());
			
			if (canditate->item.getForces().isMoving != true)
			{
				canditate->item.getForces().isMoving = true;
				m_ActiveObjs.push_back(canditate);

			}
			
			break;
			

		}

		m_QuadTree.relocate(circle, circle->item.getCollisionBox());


		++activeIt;
	}

}

void AppLayer::transferVelocity(KineticCircle& circle1, KineticCircle& circle2)
{
	auto& bodyA = circle1.getForces();
	auto& bodyB = circle2.getForces();


	Vector2 delta = Vector2Subtract(circle2.getPos(), circle1.getPos());
	float distance = Vector2Length(delta);

	Vector2 normal = Vector2Scale(delta, 1.0f / distance);

	Vector2 tangent{ -normal.y,normal.x };

	float dotProdTan1 = Vector2DotProduct(bodyA.velocity, tangent);
	float dotProdTan2 = Vector2DotProduct(bodyB.velocity, tangent);

	float dotProdNorm1 = Vector2DotProduct(bodyA.velocity, normal);
	float dotProdNorm2 = Vector2DotProduct(bodyB.velocity, normal);

	float m1 = 0.5f * (dotProdNorm1 * (bodyA.mass - bodyB.mass) + 2.0f * bodyB.mass * dotProdNorm2) / (bodyA.mass + bodyB.mass);
	float m2 =        (dotProdNorm2 * (bodyB.mass - bodyA.mass) + 2.0f * bodyA.mass * dotProdNorm1) / (bodyA.mass + bodyB.mass);

	float overlap = circle1.getRadius() + circle2.getRadius() - distance;

	if (overlap > 0.0f)
	{
		float inverseMassA = 1.0f / bodyA.mass;
		float inverseMassB = 1.0f / bodyB.mass;

		Vector2 correction = Vector2Scale(normal,overlap / (inverseMassA + inverseMassB));

		circle1.getPosition() = Vector2Subtract(circle1.getPosition(),Vector2Scale(correction, inverseMassA));

		circle2.getPosition() = Vector2Add(circle2.getPosition(),Vector2Scale(correction, inverseMassB));
	}

	bodyA.velocity = Vector2Add(Vector2Scale(tangent, dotProdTan1), Vector2Scale(normal, m1));
	bodyB.velocity = Vector2Add(Vector2Scale(tangent, dotProdTan2), Vector2Scale(normal, m2));

}

void AppLayer::checkForLayerSwitching()
{
	
	if (IsKeyPressed(KEY_ESCAPE))
	{
		Application::Get().SwitchLayer<MenuLayer>();
	}

}
