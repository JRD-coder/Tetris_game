# Furious 4

# Tetris Game - OOPS

## Introduction
This project is a **Tetris Game** implemented in **C++**, utilizing various **object-oriented programming (OOP) principles** and **data structures** such as **2D arrays** and **vectors**. The game runs in a **console window** and allows the player to control falling tetrominoes, rotate them, and clear lines to score points.

## **Game Mechanics**
- **Falling Blocks:** Tetrominoes descend from the top of the screen.
- **Player Control:** Move left, right, rotate, and drop tetrominoes.
- **Line Clearing:** Completed horizontal lines are cleared, and points are awarded.
- **Game Over Condition:** If tetrominoes stack to the top, the game ends.

## **Data Structures Used**
### **1. 2D Array (`char a[height][width]`)**
- **Purpose:** Represents the game board.
- **Usage:**
  - Stores walls (`#`), empty spaces (` `).
  - Used in the `gameboard` class to render the play area.

### **2. Vector (for Tetromino Shapes)**
- **Usage:** Each tetromino type (L, O, T, J, S, Z, I) is stored as a **4x4 vector**.
- **Operations:**
  - Rotation is implemented by transposing and reversing rows.
  - Movement is checked against boundaries and existing blocks.

### **3. Class-Based Object Organization**
#### **Class `tetro_block` (Handles Tetrominoes)**
- Stores shape, position, and movement.
- Handles rotation and collision detection.
- Implements **soft drop**, **hard drop**, and **block placement**.

#### **Class `gameboard` (Manages the Game State)**
- Initializes the board.
- Draws tetrominoes and updates the display efficiently.
- Detects and clears completed lines.
- Implements user input handling for **movement, rotation, and drop**.

## **Controls**
| Key | Action |
|-----|--------|
| Left Arrow / A | Move Left |
| Right Arrow / D | Move Right |
| Up Arrow / W | Rotate |
| Down Arrow / S | Soft Drop |
| Spacebar | Hard Drop |
| Q | Quit |
| R | Restart |

## **Optimizations & Features**
- **Optimized Rendering:** Uses `SetConsoleCursorPosition` to prevent flickering.
- **Smooth Movement:** `_kbhit()` for real-time input.
- **Next Block Preview:** Displays the upcoming tetromino.
- **Scoring System:** Earn points for clearing lines.

## **How to Run the Game**
1. Compile the C++ code using `g++` or any compatible compiler.
2. Run the executable.
3. Control the tetrominoes using the keys listed above.
4. Clear lines and score points!

## **Conclusion**
This Tetris implementation demonstrates the use of **OOP principles**, **vector-based data structures**, and **efficient console rendering techniques** to create an engaging game. The **dynamic tetromino handling** and **real-time input processing** make for smooth gameplay.

