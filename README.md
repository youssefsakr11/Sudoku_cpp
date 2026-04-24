# 🧩 Sudoku Game – Best Project Award Winner 🏆

A complete, playable Sudoku game built in **C++/CLI** with **Windows Forms**, featuring multiple difficulty levels, a heart-based mistake system, and a full solution viewer.

This project was developed as part of an academic course at **Misr International University** and won **🏅 Best Project** recognition.

---

## 🎯 Project Highlights

- ✅ Fully graphical Sudoku game (Windows Forms)
- ✅ Three difficulty levels: **Easy**, **Medium**, **Hard**
- ✅ **Heart system** – 3 lives per game
- ✅ Mistake tracking with immediate feedback
- ✅ **Show Solution** button
- ✅ Progressive difficulty – beat Easy → unlock Medium → unlock Hard
- ✅ Reset game at any time
- ✅ Clean, color-coded 9×9 grid with 3×3 subgrid shading

---

## 🛠️ Technologies Used

| Category       | Technologies                          |
|----------------|----------------------------------------|
| Language       | C++ / CLI (managed C++)                |
| UI Framework   | Windows Forms (.NET)                   |
| Backend Logic  | Custom Sudoku solver & generator       |
| Data Structures| Custom `HashMap` for player moves      |

---

## 🧠 Key Features Explained

### 🎮 Game Flow

1. **Welcome Screen** → Press Play
2. **Difficulty Selection** → Easy / Medium / Hard
3. **Game Grid** → Fill in numbers using the number pad
4. **Mistakes** → Wrong moves cost 1 heart (max 3 hearts)
5. **Victory / Game Over** → Option to continue or restart

### 🔁 Difficulty Progression

| Difficulty | Pre-filled Cells | Unlocks next? |
|------------|------------------|----------------|
| Easy       | ~35 cells         | Yes → Medium   |
| Medium     | ~25 cells         | Yes → Hard     |
| Hard       | ~20 cells         | No (win again) |

### ❤️ Heart System

- Starts with **3 hearts**
- Each incorrect number placement → **-1 heart**
- At 0 hearts → **Game Over** with restart option

### 🔍 Show Solution

- Opens a separate window with the **full solved Sudoku grid**
- Read-only view – does not affect active game

---

## 📁 Project Structure
📦 SudokuGame/
├── 📄 MyForm.cpp # Entry point (main)
├── 📄 MyForm.h # Welcome screen
├── 📄 D.h # Difficulty selection window
├── 📄 G.h # Main game grid & logic
├── 📄 Sudoku.h # Sudoku class + HashMap
├── 📄 Sudoku.cpp # Puzzle generation & solving
├── 📄 SolutionForm.h # Solution viewer window
└── 📄 Project_Sudoku.vcxproj # Visual Studio project file

## 🚀 How to Run

### Prerequisites

- **Visual Studio** (2019 or 2022) with:
  - Desktop development with C++
  - .NET desktop development workload
- Windows OS

### Steps

1. Open `Project_Sudoku.vcxproj` in Visual Studio
2. Build the solution (Ctrl+Shift+B)
3. Run (F5)

> ⚠️ This project uses **C++/CLI** and Windows Forms – Windows only.
