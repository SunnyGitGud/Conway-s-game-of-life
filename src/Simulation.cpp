#include "Simulation.hpp"
#include <vector>
#include <utility>


void Simulation::Draw()
{
   grid.Draw() ;
}

void Simulation::setCellValue(int row, int column, int value){
    grid.SetValue(row, column, value);
}

int Simulation::CountLiveNeighbors(int row, int column)
{ 
    int liveNeighbors = 0;
    std::vector<std::pair<int, int>> neighborOffsets =
    {
        {-1, 0}, //directly abve
        {1, 0},// directly below
        {0, -1},// to the left
        {0, 1},// to the right
        {-1, -1},//Diagonal upper left
        {-1, 1}, // Diagonal upper right
        {1, -1},//diagonal lower left
        {1, 1} //diagonal lower right
    };

    for (const auto& offset : neighborOffsets)
    {
        int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
        int neighborColumn = (column + offset.second + grid.Getcolumns()) % grid.Getcolumns();

        liveNeighbors += grid.GetValue(neighborRow, neighborColumn);
    }
    return liveNeighbors;

}

void Simulation::Update()
{
    if(isRunning())
    {
        for (int row = 0; row < grid.GetRows(); row++)
        {
            for (int column = 0; column < grid.Getcolumns(); column++)
            {
                int liveNeighbors = CountLiveNeighbors(row, column);
                int cellValue = grid.GetValue(row, column);

                if(cellValue == 1)
                {
                    if(liveNeighbors > 3 || liveNeighbors < 2 ) 
                    {
                        tempGrid.SetValue(row, column, 0);
                    }
                    else
                    {
                        tempGrid.SetValue(row, column, 1);
                    }
                }
                else
                {
                    if (liveNeighbors == 3)
                    {
                        tempGrid.SetValue(row, column, 1);
                    }
                    else
                    {
                        tempGrid.SetValue(row, column, 0);
                    }
                }
            }
        }
        grid = tempGrid;
    }
}

void Simulation::ClearGrid()
{
    if (!isRunning())
    {
        grid.Clear();
    }
}

void Simulation::CreateRandomState()
{
    grid.FillRandom();
}

void Simulation::ToggleCell(int row, int column)
{
    if(!isRunning())
{
    grid.ToggleCell(row, column);
}
}