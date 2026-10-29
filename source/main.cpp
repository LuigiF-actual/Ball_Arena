// Ball_Arena.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <raylib.h>

#include "Objects/include/Application.hpp"
#include "Layers/include/AppLayer.hpp"
#include "Layers/include/MenuLayer.hpp"

#define GUI_POINTER_POSITION Application::Get().GetMouseInRenderTexture()
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <examples/styles/style_cyber.h>

int main()
{
    ApplicationSpecification appSpec;
    appSpec.Name = "Ball_Arena";
    appSpec.Width = 1280;
    appSpec.Height = 720;
    appSpec.VSync = false;
    appSpec.IsResizeable = false;


    Application app(appSpec);
       
    auto menuLayer = std::make_unique<MenuLayer>();
    menuLayer->SetUi(true);
    auto appLayer = std::make_unique<AppLayer>();
    appLayer->SetActive(false);

    SetExitKey(NULL);

    GuiSetStyle(LABEL, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
    GuiLoadStyleCyber();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 56);
  

    app.PushLayer(std::move(appLayer));
    app.PushLayer(std::move(menuLayer));
    app.Run();


	return 0;
}
