// Ball_Arena.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <raylib.h>

int main()
{
	std::cout << "Hello CMake." << std::endl;

	InitWindow(720, 720, "Ball_Arena");


    SetTargetFPS(60);             

    while (!WindowShouldClose())   
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Testing! 1 2 3", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();       

	return 0;
}
