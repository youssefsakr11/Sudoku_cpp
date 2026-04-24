//Game Grid 
#pragma once
#include "Sudoku.h"
#include "SolutionForm.h"
#include <msclr/marshal_cppstd.h>

namespace sudoku_window {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class G : public Form {
    private:
        Sudoku* game;
        String^ difficulty;
        cli::array<Button^, 2>^ gridButtons;
        cli::array<Button^>^ numberButtons;
        Button^ selectedCell;
        Label^ heartsLabel;

        void InitializeComponent() {
            this->Text = "Sudoku Game";
            this->ClientSize = System::Drawing::Size(400, 550);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->MaximizeBox = false;

            gridButtons = gcnew cli::array<Button^, 2>(9, 9);
            numberButtons = gcnew cli::array<Button^>(9);

            int gridCellSize = 40;
            int padding = 20;

            for (int row = 0; row < 9; row++) {
                for (int col = 0; col < 9; col++) {
                    Button^ button = gcnew Button();
                    button->Size = System::Drawing::Size(gridCellSize, gridCellSize);
                    button->Location = System::Drawing::Point(padding + col * gridCellSize, padding + row * gridCellSize);
                    button->BackColor = ((row / 3 + col / 3) % 2 == 0) ? Color::LightGray : Color::White;
                    button->FlatStyle = FlatStyle::Flat;
                    button->Tag = gcnew cli::array<int>(2) { row, col };
                    button->Click += gcnew EventHandler(this, &G::GridButton_Click);
                    gridButtons[row, col] = button;
                    this->Controls->Add(button);
                }
            }

            int numberPadY = padding + 9 * gridCellSize + 20;

            for (int i = 0; i < 9; i++) {
                Button^ button = gcnew Button();
                button->Text = (i + 1).ToString();
                button->Size = System::Drawing::Size(gridCellSize, gridCellSize);
                button->Location = System::Drawing::Point(padding + i * gridCellSize, numberPadY);
                button->Font = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
                button->Tag = i + 1;
                button->Click += gcnew EventHandler(this, &G::NumberButton_Click);
                numberButtons[i] = button;
                this->Controls->Add(button);
            }

            heartsLabel = gcnew Label();
            heartsLabel->Text = "Hearts Remaining: 3";
            heartsLabel->Location = System::Drawing::Point(padding, numberPadY + gridCellSize + 10);
            heartsLabel->AutoSize = true;
            this->Controls->Add(heartsLabel);

            Button^ resetButton = gcnew Button();
            resetButton->Text = "Reset";
            resetButton->Location = System::Drawing::Point(300, numberPadY + gridCellSize + 10);
            resetButton->Click += gcnew EventHandler(this, &G::ResetButton_Click);
            this->Controls->Add(resetButton);

            Button^ solutionButton = gcnew Button();
            solutionButton->Text = "Show Solution";
            solutionButton->Location = System::Drawing::Point(150, numberPadY + gridCellSize + 10);
            solutionButton->Click += gcnew EventHandler(this, &G::SolutionButton_Click);
            this->Controls->Add(solutionButton);
        }

        void UpdateGrid() {
            for (int row = 0; row < 9; row++) {
                for (int col = 0; col < 9; col++) {
                    if (game == nullptr) return; // Safeguard in case game is not initialized
                    int value = game->getGridValue(row, col);
                    if (value != 0) {
                        gridButtons[row, col]->Text = value.ToString();
                        gridButtons[row, col]->Enabled = false;
                    }
                    else {
                        gridButtons[row, col]->Text = "";
                        gridButtons[row, col]->Enabled = true;
                    }
                }
            }
        }

        void GridButton_Click(Object^ sender, EventArgs^ e) {
            Button^ clickedButton = safe_cast<Button^>(sender);
            if (selectedCell != nullptr) {
                selectedCell->FlatAppearance->BorderColor = Color::Black;
            }
            selectedCell = clickedButton;
            selectedCell->FlatAppearance->BorderColor = Color::Blue;
        }

        void NumberButton_Click(Object^ sender, EventArgs^ e) {
            if (selectedCell == nullptr || selectedCell->Tag == nullptr) return; // Ensure selectedCell is valid

            Button^ numberButton = safe_cast<Button^>(sender);
            int number = safe_cast<int>(numberButton->Tag);
            cli::array<int>^ position = safe_cast<cli::array<int>^>(selectedCell->Tag);

            int row = position[0];
            int col = position[1];

            if (game == nullptr || gridButtons[row, col] == nullptr) return; // Additional safeguard

            // Main game logic
            if (game->getGridValue(row, col) != 0) {
                return; // Skip if cell is part of the initial puzzle
            }

            if (game->isValid(row, col, number)) {
                game->setGridValue(row, col, number);
                selectedCell->Text = number.ToString();
                selectedCell->Enabled = false;
                selectedCell->FlatAppearance->BorderColor = Color::Black;
                selectedCell = nullptr;

                if (CheckWin()) {
                    System::Windows::Forms::DialogResult result;
                    if (difficulty == "easy") {
                        result = MessageBox::Show(
                            "Congratulations! You've solved the puzzle.\nDo you want to go to the next level (medium)?",
                            "Victory",
                            MessageBoxButtons::YesNo,
                            MessageBoxIcon::Question
                        );
                        if (result == System::Windows::Forms::DialogResult::Yes) {
                            difficulty = "medium";
                            ResetGame();
                        }
                        else {
                            this->Close();
                        }
                    }
                    else if (difficulty == "medium") {
                        result = MessageBox::Show(
                            "Congratulations! You've solved the puzzle.\nDo you want to go to the next level (hard)?",
                            "Victory",
                            MessageBoxButtons::YesNo,
                            MessageBoxIcon::Question
                        );
                        if (result == System::Windows::Forms::DialogResult::Yes) {
                            difficulty = "hard";
                            ResetGame();
                        }
                        else {
                            this->Close();
                        }
                    }
                    else {
                        result = MessageBox::Show(
                            "Congratulations! You've solved the puzzle.\nDo you want to play again?",
                            "Victory",
                            MessageBoxButtons::YesNo,
                            MessageBoxIcon::Question
                        );
                        if (result == System::Windows::Forms::DialogResult::Yes) {
                            ResetGame();
                        }
                        else {
                            this->Close();
                        }
                    }
                }
            }
            else {
                MessageBox::Show("Wrong insertion! Try again.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                game->decreaseHearts();
            }

            heartsLabel->Text = "Hearts Remaining: " + game->getHeartsRemaining().ToString();
            if (game->getHeartsRemaining() == 0) {
                System::Windows::Forms::DialogResult result = MessageBox::Show(
                    "Game Over! Too many mistakes. Do you want to play again?",
                    "Game Over",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Question
                );

                if (result == System::Windows::Forms::DialogResult::Yes) {
                    ResetGame();
                }
                else {
                    this->Close();
                }
            }
        }

        void ResetButton_Click(Object^ sender, EventArgs^ e) {
            ResetGame();
        }

        void SolutionButton_Click(Object^ sender, EventArgs^ e) {
            if (game == nullptr) return; // Safeguard
            SolutionForm^ solutionForm = gcnew SolutionForm(game);
            solutionForm->ShowDialog();
        }

        bool CheckWin() {
            if (game == nullptr) return false; // Safeguard
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (game->getGridValue(i, j) != game->getSolutionValue(i, j)) {
                        return false;
                    }
                }
            }
            return true;
        }

        void ResetGame() {
            if (game == nullptr) {
                game = new Sudoku(); // Reinitialize game if null
            }
            msclr::interop::marshal_context context;
            const char* diff = context.marshal_as<const char*>(difficulty);
            game->resetGame();
            game->startGame(diff);
            UpdateGrid();
            heartsLabel->Text = "Hearts Remaining: 3";
        }

    public:
        G(String^ difficulty) {
            this->difficulty = difficulty;
            game = new Sudoku();
            srand(static_cast<unsigned>(time(0)));
            InitializeComponent();
            ResetGame();
        }

        ~G() {
            if (game) delete game;
        }
    };
}