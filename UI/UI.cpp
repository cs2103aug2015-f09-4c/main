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

void UI::Swiftask::updateOutputBox(void) {
	clearOutputBox();
	displayInOutputBox();

	return;
}

void UI::Swiftask::clearOutputBox(void) {

	while (outputBox->DisplayedRowCount(true)) {
		outputBox->Rows->RemoveAt(0);
	}
	return;
}

void UI::Swiftask::displayInOutputBox(void) {
	System::String ^str1, ^str2, ^str3, ^str4;

	for (std::vector<API::Task>::iterator it = (*feedback).getTasksForDisplay().begin(); it < (*feedback).getTasksForDisplay().end(); it++) {
		str1 = gcnew String((*it).getTaskText().c_str());

		if (!(*it).getStartDateTime().is_not_a_date_time()) {
			str2 = gcnew String(to_simple_string((*it).getStartDateTime()).c_str());
		} else {
			str2 = gcnew String("-");
		}

		if (!(*it).getEndDateTime().is_not_a_date_time()) {
			str3 = gcnew String(to_simple_string((*it).getEndDateTime()).c_str());
		} else {
			str3 = gcnew String("-");
		}

		// Tags not supported yet
		// if ((*it).getTags != "") {
		// 	str4 = gcnew String((*it).getTags.c_str());
		// } else {
			str4 = gcnew String("-");
		// }
		outputBox->Rows->Add(str1, str2, str3, str4);

		delete str1;
		delete str2;
		delete str3;
		delete str4;
	}
	return;
}
