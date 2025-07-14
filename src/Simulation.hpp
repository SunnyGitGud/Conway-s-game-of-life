#pragma once
#include "grid.hpp"

class Simulation
{
private:
    Grid grid;
    Grid tempGrid;
    bool run;
public:
    Simulation(int width, int height, int cellSize)
    : grid(width, height, cellSize),
    tempGrid(width, height, cellSize), run(false)  {};

    void Draw();
    void setCellValue(int row, int column, int value);

    int CountLiveNeighbors(int row, int column);
    void Update();
    bool isRunning() {return run;}
    void start() {run = true;}
    void stop() {run = false;}
    void ClearGrid();
    void CreateRandomState();
    void ToggleCell(int row,int column);

};

