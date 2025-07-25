#include "grid.hpp"
#include <raylib.h>

bool Grid::isWithinBounds(int row, int column)
{
    if(row >= 0 && row < rows && column >= 0 && column < columns)
    {
        return true;
    }
    return false;
}

void Grid::Draw()
{   
    for(int row = 0; row < rows; row++ )
    {
        for (int column = 0; column < columns; column++)
        {
            Color color = cells[row][column] 
                ? Color { 0 , 255, 0, 255}
                    : Color{55, 55, 55, 255};
            DrawRectangle(column * cellSize, row * cellSize, cellSize -1 , cellSize-1, color);                
        }
    }
}

void Grid::SetValue(int row, int column, int value)
{
    if(isWithinBounds(row, column))
    {
        cells[row][column] = value; 
    }
}

int Grid::GetValue(int row, int column)
{
   if(isWithinBounds(row, column))
   {
    return cells[row][column];
   }
   return 0;
}

void Grid::FillRandom()
{
    for(int row = 0; row < rows; row++)
    {
        for (int column = 0; column < columns; column++)
        {
            int randomValue = GetRandomValue(0, 4);
            cells[row][column] = (randomValue == 4) ? 1 : 0;
        }
    }
}

void Grid::Clear()
{
    for(int row =0; row < rows; row++)
    {
        for(int column = 0; column < columns; column++)
        {
            cells[row][column] = 0;
        }
    }
}

void Grid::ToggleCell(int row, int column)
{
    if (isWithinBounds(row, column))
    {
        cells[row][column] =! cells[row][column];
    }
}
