#include "UI.h"
#include "Logic.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	UI::Swiftask mainWindow;
	Application::Run(%mainWindow);
}