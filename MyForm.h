// Main.cpp
#include "MyForm.h"
#include <iostream>

using namespace std;
using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main() {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew sudoku_window::MyForm());
    return 0;
}