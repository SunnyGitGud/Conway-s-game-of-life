#pragma once
#include <vector>



class Grid
{
private:
    int rows; 
    int columns;
    int cellSize;
    std::vector<std::vector<int>> cells;
    bool isWithinBounds(int row, int column);
public:
    Grid(int Width, int Height, int cellSize)
    : rows(Height/cellSize), columns(Width/cellSize), cellSize(cellSize),
    cells(rows, std::vector<int>(columns,0)){};

    void Draw();
    void SetValue(int row, int column, int value);
    int GetValue(int row, int column);
    int GetRows() {return rows;};
    int Getcolumns() {return columns;};
    void FillRandom();
    void Clear();
    void ToggleCell(int row, int column);
};

