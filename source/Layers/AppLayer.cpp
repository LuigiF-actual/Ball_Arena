#include "include/AppLayer.hpp"


AppLayer::AppLayer()
{
	std::print("AppCreated!");
}

void AppLayer::OnUpdate()
{

}


void AppLayer::OnRender()
{

	DrawRectangleRec(myRec, RED);
	DrawFPS(0,0);
}
