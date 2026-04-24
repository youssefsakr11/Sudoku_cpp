//Welcome window
#pragma once
#include "D.h"

namespace sudoku_window {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class MyForm : public Form {
    private:
        void InitializeComponent() {
            this->Text = "Welcome to Sudoku";
            this->ClientSize = System::Drawing::Size(400, 300);
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->StartPosition = FormStartPosition::CenterScreen;
            this->MaximizeBox = false;

            Label^ welcomeLabel = gcnew Label();
            welcomeLabel->Text = "Welcome to Sudoku!";
            welcomeLabel->Font = gcnew System::Drawing::Font("Arial", 24, FontStyle::Bold);
            welcomeLabel->AutoSize = true;
            welcomeLabel->Location = System::Drawing::Point(70, 100);

            Button^ playButton = gcnew Button();
            playButton->Text = "Play";
            playButton->Size = System::Drawing::Size(100, 40);
            playButton->Location = System::Drawing::Point(150, 180);
            playButton->Font = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
            playButton->Click += gcnew EventHandler(this, &MyForm::PlayButton_Click);

            this->Controls->Add(welcomeLabel);
            this->Controls->Add(playButton);
        }

        void PlayButton_Click(Object^ sender, EventArgs^ e) {
            this->Hide();
            D^ difficultyForm = gcnew D();
            difficultyForm->ShowDialog();
            this->Close();
        }

    public:
        MyForm() {
            InitializeComponent();
        }
    };
}