// Ball_Arena.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <raylib.h>

#include "Objects/include/Application.hpp"
#include "Layers/include/AppLayer.hpp"

int main()
{
	std::cout << "Hello CMake." << std::endl;

    ApplicationSpecification appSpec;
    appSpec.Name = "Ball_Arena";
    appSpec.Width = 720;
    appSpec.Height = 720;
    appSpec.VSync = false;


    Application app(appSpec);
    app.PushLayer<AppLayer>();
    app.Run();


	return 0;
}
