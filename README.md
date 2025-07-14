
# Conway's Game of Life - Code Documentation & Explanation

This document explains the complete structure and logic of a 2D cellular automata simulation based on **Conway's Game of Life**, built using C++ and Raylib. It is designed to be easy to follow and serves as a study reference.

---

## 🧠 Concept: Conway's Game of Life
Conway's Game of Life is a simple but fascinating example of **cellular automata**. Each cell on a grid is either **alive (1)** or **dead (0)**, and its state updates based on the number of live neighbors it has.

### 👥 Neighbor Structure
Each cell checks its 8 surrounding neighbors:

```
[(-1,-1)] [(-1, 0)] [(-1,+1)]
[( 0,-1)] [ Cell  ] [( 0,+1)]
[(+1,-1)] [(+1, 0)] [(+1,+1)]
```

### 📜 Rules Table
| Current State | Live Neighbors | Next State | Description            |
|---------------|----------------|------------|------------------------|
| Alive         | < 2            | Dead       | Underpopulation        |
| Alive         | 2 or 3         | Alive      | Survival               |
| Alive         | > 3            | Dead       | Overpopulation         |
| Dead          | == 3           | Alive      | Reproduction           |

These simple rules result in surprisingly complex behavior when the grid is updated over time.

---

## 🌐 Toroidal Grid: Edge Wrapping Explained
In our simulation, the grid is **toroidal**, which means it wraps around like a donut:

### Why?
Cells on the edge still need 8 neighbors. Instead of leaving them out-of-bounds, we wrap around:
- Left edge connects to right
- Top edge connects to bottom

### Visualization:
```
Imagine this 3x3 grid:

A B C
D E F
G H I

If E is the center cell, its top neighbor A wraps around from bottom if it’s on the first row. Same applies for left/right edges.
```

### C++ Implementation:
```cpp
int neighborRow = (row + offset.first + grid.GetRows()) % grid.GetRows();
int neighborColumn = (column + offset.second + grid.Getcolumns()) % grid.Getcolumns();
```
This keeps all indices within bounds by wrapping around.

---

## 📂 Project File Structure
| File                | Purpose                                      |
|---------------------|----------------------------------------------|
| `main.cpp`          | App entry point & input handling              |
| `Simulation.hpp/cpp`| Logic for running the simulation             |
| `grid.hpp/cpp`      | Defines how cells are stored, drawn, toggled |

---

## 🖼️ grid.hpp / grid.cpp
### Grid Class: Manages 2D Cell State
#### Core Attributes
```cpp
int rows, columns;
std::vector<std::vector<int>> cells;
```

#### Grid Initialization Logic
The number of rows and columns is dynamically calculated based on the window dimensions and cell size:
```cpp
Grid(int Width, int Height, int cellSize)
    : rows(Height / cellSize),
      columns(Width / cellSize),
      cellSize(cellSize),
      cells(rows, std::vector<int>(columns, 0)) {}
```
- `Height / cellSize` determines how many cells fit vertically.
- `Width / cellSize` determines how many fit horizontally.
- Each cell is initialized to `0` (dead).

This ensures that the grid automatically fits the window size.

#### Methods
- `Draw()` — Draws every cell using a color based on its state:
  - Alive (`1`): Bright green (`Color{0, 255, 0, 255}`)
  - Dead (`0`): Dark grey (`Color{55, 55, 55, 255}`)

```cpp
Color color = cells[row][column] 
    ? Color{0, 255, 0, 255} 
    : Color{55, 55, 55, 255};
DrawRectangle(column * cellSize, row * cellSize, cellSize - 1, cellSize - 1, color);
```
This also leaves a 1-pixel gap between cells for a visible grid.

- `SetValue()` / `GetValue()` — Sets/gets cell state
- `ToggleCell()` — Flips cell's state on click
- `FillRandom()` — Random 1-in-5 cells made alive
- `Clear()` — All cells made dead

---

## 🧮 Simulation.hpp / Simulation.cpp
### Simulation Class: Governs Rules and Evolution
Contains:
- `grid`: current generation
- `tempGrid`: next generation (used to avoid corruption during updates)

### ❗ Why use `tempGrid`?
When applying the rules of the Game of Life, we must look at the **original state of all cells** to compute the next state correctly.

If we were to update `grid` directly, then some cells would be based on already updated neighbors — which breaks the rules.

Instead, we:
1. Calculate the next state for each cell based on the current `grid`.
2. Store it in `tempGrid`.
3. After all cells are processed, copy `tempGrid` back to `grid`.

This technique is called **double buffering** and ensures correctness.

#### 🧠 CountLiveNeighbors()
Loops through all 8 offsets, applies **toroidal wrapping**, then counts live cells.

#### 🔁 Update()
Applies Game of Life rules:
```cpp
if (alive && (neighbors < 2 || neighbors > 3)) -> Die
if (!alive && neighbors == 3) -> Become alive
else -> Stay the same
```

#### Other Methods
- `start()` / `stop()` / `isRunning()` — simulation control
- `ToggleCell()` — allows mouse editing
- `ClearGrid()`, `CreateRandomState()`

---

## 🧵 main.cpp
### Core Setup
- Initializes Raylib window
- Sets target FPS
- Instantiates Simulation object

### Event Handling
| Input       | Action                        |
|-------------|-------------------------------|
| `Mouse LMB` | Toggle cell alive/dead        |
| `Enter`     | Start simulation              |
| `Space`     | Stop simulation               |
| `R`         | Fill grid randomly            |
| `C`         | Clear grid                    |
| `F`         | Increase simulation speed     |
| `S`         | Decrease simulation speed     |

### Main Loop
```cpp
simulation.Update();
simulation.Draw();
```
- Every frame, logic is updated and new state is rendered.

---

## 🧩 How Everything Fits Together
```
[main.cpp] --> Controls app and input
     ↓
[Simulation] --> Applies life rules
     ↓
[Grid] --> Stores and draws state
```
This clean separation makes the simulation easy to understand and expand.

---

## 💡 Key Takeaways
- OOP Design: Grid and Simulation separate responsibilities
- Toroidal Wrapping: Elegant use of modulo
- Double Buffering: `tempGrid` avoids inconsistent updates
- Grid Sizing: Automatically fits cells to screen using `cellSize`
- Grid Rendering: Alive cells drawn bright green, dead cells grey
- Cellular Automata: Shows emergent behavior from simple rules
- Real-Time Rendering: Uses Raylib to visualize generations

---

## 🌱 Ideas for Extension
- Load/save grid state
- Preset patterns (gliders, blinkers, etc.)
- Color fading for old cells
- Click & drag brush mode
- Time-based step counter

---

## 📋 Final Thoughts
This simulator captures the core beauty of Conway’s Game of Life while staying beginner-friendly in its design. With good abstraction, clean logic, and interactive controls, it’s a solid foundation for deeper explorations into simulations, visualization, and game development.

Let me know if you want a downloadable Markdown or PDF version!
