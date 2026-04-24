// Solution Grid
#pragma once
#include "Sudoku.h"

namespace sudoku_window {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class SolutionForm : public Form {
    private:
        Sudoku* game;

        void InitializeComponent() {
            this->Text = "Sudoku Solution";
            this->ClientSize = System::Drawing::Size(400, 400);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->StartPosition = FormStartPosition::CenterScreen;

            int gridCellSize = 40;
            int padding = 20;

            for (int row = 0; row < 9; row++) {
                for (int col = 0; col < 9; col++) {
                    Button^ button = gcnew Button();
                    button->Size = System::Drawing::Size(gridCellSize, gridCellSize);
                    button->Location = System::Drawing::Point(padding + col * gridCellSize, padding + row * gridCellSize);
                    button->FlatStyle = FlatStyle::Flat;
                    button->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
                    button->ForeColor = Color::FromArgb(0, 0, 0); // Very dark black
                    button->BackColor = ((row / 3 + col / 3) % 2 == 0) ? Color::LightGray : Color::White;
                    button->Enabled = false;
                    button->Text = game->getSolutionValue(row, col).ToString();
                    this->Controls->Add(button);
                }
            }
        }

    public:
        SolutionForm(Sudoku* sudokuGame) {
            game = sudokuGame;
            InitializeComponent();
        }
    };
}