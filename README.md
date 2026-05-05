# 🧩 Sudoku Game


## 📌 Overview

This project is a **Sudoku desktop game** built using **C++/CLI** and **.NET Windows Forms**.
It demonstrates object-based programming, GUI development, and basic algorithm implementation.

---

## 🎯 Features

* 🎮 3 Difficulty Levels (Easy, Medium, Hard)
* ❤️ 3 Hearts system (lose one on wrong move)
* 🔓 Progressive difficulty unlocking
* 🔍 Solution viewer window
* 🎨 Clean 9×9 grid with styled sections
* 🔄 Reset game anytime

---

## 🧠 Concepts Used

* Object-Based Design
  
The application is structured around classes (e.g., Sudoku, UI handlers), promoting modularity, code organization, and reusability.

* Event-Driven Programming
  
User interactions (button clicks, cell selection) trigger events that control game behavior, making the application responsive and interactive.

* Recursive Backtracking Algorithm
  
Used to solve and validate the Sudoku grid. This approach systematically tries possible values and backtracks when constraints are violated.

* State Management
  
The game tracks user progress, including filled cells, remaining lives (hearts), and current difficulty level.

* Custom Data Handling
  
A simple custom structure (e.g., a HashMap-like approach) is used to store and manage user inputs efficiently.

* GUI Logic Separation
  
Separation between game logic and UI improves maintainability and makes the code easier to extend or debug.

---

## 🎮 How to Play

1. Run the application
2. Choose difficulty
3. Select a cell
4. Enter a number (1–9)

* ✅ Correct → stays
* ❌ Wrong → lose a heart

Win by completing the grid.
Lose when hearts reach 0.

---

## 🛠️ Technologies

* C++/CLI (Managed C++)

Used to implement the core application logic while leveraging .NET libraries. It allows seamless interaction between native C++ code and the managed runtime.


* .NET Windows Forms

Provides the graphical user interface (GUI), including event-driven components such as buttons, grids, and forms for user interaction.


* Visual Studio

Used as the development environment for building, debugging, and managing the project.

---

## 🚀 How to Run

### Requirements

* Windows OS
* Visual Studio (with C++ and .NET workloads)

### Steps

1. Clone the repository
2. Open project in Visual Studio
3. Build (Ctrl + Shift + B)
4. Run (F5)

---

## 📁 Project Structure

Sudoku-Game/
│
├── MyForm.cpp

├── MyForm.h

├── D.h

├── G.h

├── Sudoku.cpp

├── Sudoku.h

├── SolutionForm.h

└── Project files


---


## 📜 License

MIT License

---

