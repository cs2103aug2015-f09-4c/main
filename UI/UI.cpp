#include "UI.h"

using namespace System;
using namespace System::Windows::Forms;

INITIALIZE_EASYLOGGINGPP

[STAThread]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	UI::Swiftask mainWindow;
	Application::Run(%mainWindow);

	return EXIT_SUCCESS;
}

std::string UI::Swiftask::getStdStringCommand(void) {
	System::String^ managed;

	managed = commandBox->Text;
	commandBox->Text = "";

	return msclr::interop::marshal_as<std::string>(managed);
}

void UI::Swiftask::updateUI(void) {
	updateResults();
	updateOutputBox();

	return;
}

void UI::Swiftask::updateResults(void) {

	System::String^ managed = gcnew String((*feedback).getFeedbackMessage().c_str());
	results->Text = managed;
	delete managed;

	return;
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
	System::String ^num, ^taskText, ^startDate, ^endDate, ^theTags, ^doneOrNot;
	int index = 0;
	std::ostringstream convert;

	for (std::vector<API::Task>::iterator it = (*feedback).getTasksForDisplay().begin(); it < (*feedback).getTasksForDisplay().end(); it++) {
		// Index implemented ahead of Logic and update in UIfeedback.
		// Logic is supposed to send tasks in order, 
		// so potential logical error (wrong numbering of tasks) may arise here.
		index++;
		convert << index;
		num = gcnew String(convert.str().c_str());
		convert.str(std::string());

		taskText = gcnew String((*it).getTaskText().c_str());

		if (!(*it).getStartDateTime().is_not_a_date_time()) {
			startDate = gcnew String(to_simple_string((*it).getStartDateTime()).c_str());
		} else {
			startDate = gcnew String("-");
		}

		if (!(*it).getEndDateTime().is_not_a_date_time()) {
			endDate = gcnew String(to_simple_string((*it).getEndDateTime()).c_str());
		} else {
			endDate = gcnew String("-");
		}

		// Tags not supported yet
		// if ((*it).getTags != "") {
		// 	str5 = gcnew String((*it).getTags.c_str());
		// } else {
		theTags = gcnew String("-");
		// }

		if ((*it).isComplete()) {
			doneOrNot = gcnew String("Yes");
		} else {
			doneOrNot = gcnew String("No");
		}

		outputBox->Rows->Add(num, taskText, startDate, endDate, theTags, doneOrNot);

		if ((*it).isComplete()) {
			outputBox->Rows[index-1]->Cells[OutputBoxColumn::DONE]->Style->ForeColor = Color::Green;
		} else {
			outputBox->Rows[index-1]->Cells[OutputBoxColumn::DONE]->Style->ForeColor = Color::Red;
		}

		// number->HeaderCell->Style->BackColor = Color::Blue;
		// outputBox->RowHeadersDefaultCellStyle->ForeColor = Color::Red;
		// Work-in-Progress 08/10/15

		delete num;
		delete taskText;
		delete start;
		delete end;
		delete tags;
		delete done;
	}
	return;
}
