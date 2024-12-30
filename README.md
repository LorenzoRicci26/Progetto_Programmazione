# 🚀 A* Pathfinding Algorithm for Grid-based Navigation

This repository contains the implementation of the **A\* (A-star) algorithm** for finding the shortest path in a grid map with obstacles. The project allows a character to navigate from a start point to a destination by following the most efficient path calculated using A\*.

## 📌 Overview

The grid represents a map where each cell is either:

- **White**: Free space where the character can move.
- **Colored**: An obstacle that blocks the character's movement.

The character starts in a specific cell and moves towards a destination cell. The user clicks on the destination, and the algorithm computes the shortest path from the start to the destination while avoiding obstacles.

---

## 🔧 Features

- **Interactive Grid**: Click anywhere on the grid to set the destination.
- **A\* Pathfinding**: The algorithm calculates the most efficient route by considering both the distance from the start and the proximity to the destination.
- **Visual Representation**: Obstacles are displayed as colored cells, while the free space is shown as white cells.
- **Real-time Animation**: The character moves step-by-step along the path, allowing you to see the algorithm in action.
- **Performance**: The algorithm efficiently handles maps of varying sizes and complexity, adapting to different grid configurations.

---

## 🧠 How It Works

1. **Grid Representation**: The map is a grid composed of cells. Each cell can either be:
   - **Empty**: The character can walk through these cells.
   - **Obstacle**: These cells block the character's movement.
   
2. **A\* Algorithm**: The A* algorithm combines:
   - **g(x)**: The cost to move from the start to the current cell.
   - **h(x)**: The estimated cost (heuristic) from the current cell to the destination.
   The algorithm selects the cell with the lowest **f(x) = g(x) + h(x)** to move to the next.

3. **User Interaction**: You can click on any cell in the grid to set the destination. The algorithm will calculate the shortest path and move the character accordingly.

4. **Path Visualization**: The calculated path is displayed, showing each step the character takes to reach the destination. Obstacles are dynamically handled during pathfinding.
