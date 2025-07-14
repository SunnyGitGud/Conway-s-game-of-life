#include <raylib.h>
#include "Simulation.hpp"
#include <iostream>


int main()
{

    Color GREY = {29, 29, 29, 255};
    const int  WINDOW_WIDTH =  1200;
    const int  WINDOW_HEIGHT =  800;
    int FPS = 12;
    const int CELL_SIZE = 10;


    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "2D generation simulator");
    SetTargetFPS(FPS);
    Simulation simulation(WINDOW_WIDTH, WINDOW_HEIGHT, CELL_SIZE);
 




    //simultaion loop
    while(WindowShouldClose() == false)
    {
        // Event handling

        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 mousePosition = GetMousePosition();
            int row = mousePosition.y/ CELL_SIZE;
            int column = mousePosition.x/ CELL_SIZE;
            simulation.ToggleCell(row, column);
        }




        if (IsKeyPressed(KEY_ENTER))
        {
            simulation.start();
            SetWindowTitle("Simulation is running .....");

        }
        else if (IsKeyPressed(KEY_SPACE))
        {
            simulation.stop();
            SetWindowTitle("Simulation Stopped.");
        }
        else if (IsKeyPressed(KEY_F))
        {
            FPS += 2;
            SetTargetFPS(FPS);
        }
        else if(IsKeyPressed(KEY_S))
        {
            if(FPS > 5)
           { FPS -= 2;
            SetTargetFPS(FPS);};
        }

        else if(IsKeyPressed(KEY_R))
        {
            simulation.CreateRandomState();
        }
        else if(IsKeyPressed(KEY_C))
        {
            simulation.ClearGrid();
        }
    
        // updating state
        simulation.Update();
        // Drawing
        BeginDrawing();
        ClearBackground(GREY);
        simulation.Draw();
        EndDrawing();

    }



    CloseWindow();
}
