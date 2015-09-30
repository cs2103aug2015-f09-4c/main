#include "UI.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	UI::Swiftask mainWindow;
	Application::Run(%mainWindow);

	return EXIT_SUCCESS;
}
