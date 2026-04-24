//Difficulty levels window
#pragma once
#include "G.h"

namespace sudoku_window {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class D : public Form {
    private:
        void InitializeComponent() {
            this->Text = "Select Difficulty";
            this->ClientSize = System::Drawing::Size(400, 400);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->MaximizeBox = false;

            Label^ titleLabel = gcnew Label();
            titleLabel->Text = "Choose Difficulty";
            titleLabel->Font = gcnew System::Drawing::Font("Arial", 20, FontStyle::Bold);
            titleLabel->AutoSize = true;
            titleLabel->Location = System::Drawing::Point(100, 50);

            cli::array<String^>^ difficulties = gcnew cli::array<String^>{ "Easy", "Medium", "Hard" };
            cli::array<String^>^ difficultyValues = gcnew cli::array<String^>{ "easy", "medium", "hard" };

            for (int i = 0; i < 3; i++) {
                Button^ diffButton = gcnew Button();
                diffButton->Text = difficulties[i];
                diffButton->Size = System::Drawing::Size(200, 50);
                diffButton->Location = System::Drawing::Point(100, 120 + i * 70);
                diffButton->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
                diffButton->Tag = difficultyValues[i];
                diffButton->Click += gcnew EventHandler(this, &D::DifficultyButton_Click);
                this->Controls->Add(diffButton);
            }

            this->Controls->Add(titleLabel);
        }

        void DifficultyButton_Click(Object^ sender, EventArgs^ e) {
            Button^ button = safe_cast<Button^>(sender);
            String^ difficulty = safe_cast<String^>(button->Tag);
            this->Hide();
            G^ gameForm = gcnew G(difficulty);
            gameForm->ShowDialog();
            this->Close();
        }

    public:
        D() {
            InitializeComponent();
        }
    };
}