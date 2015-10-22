#include "UI.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args) {
	Logger* logger = Logger::getInstance();

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	UI::Swiftask mainWindow;
	Application::Run(%mainWindow);

	return EXIT_SUCCESS;
}

void UI::Swiftask::updateAutoComplete(std::vector<std::string> lines) {
	// TODO: implement this function

	//commandBox->AutoCompleteCustomSource->AddRange(gcnew cli::array< System::String^  >(13) {L"add ", L"complete ", L"delete ", 
	//			L"display", L"edit name ", L"edit start ", L"edit end ", L"exit ", L"search ", L"sort ", L"tag ", L"undo", L"untag "});
	return;
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
	System::String ^num = "";
	System::String ^taskText = "";
	System::String ^startDateTime = "";
	System::String ^endDateTime = "";
	System::String ^theTags = "";
	System::String ^doneOrNot = "";
	boost::posix_time::ptime posixStartDateTime;
	boost::posix_time::ptime posixEndDateTime;
	boost::posix_time::ptime posixNowDateTime;
	int index = 0;
	bool isCompleted = false;
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

		posixStartDateTime = (*it).getStartDateTime();
		if (!posixStartDateTime.is_not_a_date_time()) {
			startDateTime = gcnew String(boost::posix_time::to_simple_string(posixStartDateTime).c_str());

		} else {
			startDateTime = gcnew String("-");
		}

		posixEndDateTime = (*it).getEndDateTime();
		if (!posixEndDateTime.is_not_a_date_time()) {
			endDateTime = gcnew String(boost::posix_time::to_simple_string(posixEndDateTime).c_str());
		} else {
			endDateTime = gcnew String("-");
		}

		std::set<std::string> tagsList;
		std::string stdTags = "";
		tagsList = (*it).getTags();
		if (tagsList.size() != 0) {
			for (std::set<std::string>::iterator iter = tagsList.begin(); iter != tagsList.end(); iter++) {
				stdTags = stdTags + (*iter);
			}
			theTags = gcnew String(stdTags.c_str());
		} else {
			theTags = gcnew String("-");
		}

		isCompleted = (*it).isComplete();
		//if (isCompleted) {
		//	doneOrNot = gcnew String("Yes");
		//} else {
		//	doneOrNot = gcnew String("No");
		//}

		outputBox->Rows->Add(num, taskText, startDateTime, endDateTime, theTags);

		// Colour Formats for outputBox
		// TODO: Refactor this section to formatOutputBoxStartEndColumn(...);
		posixNowDateTime = boost::posix_time::second_clock::local_time();

		if (!isCompleted && startDateTime != "-") {
			if (posixStartDateTime <= posixNowDateTime) {
				outputBox->Rows[index-1]->Cells[OutputBoxColumn::START]->Style->BackColor = Color::Lime;
			}
		}

		if (!isCompleted && endDateTime != "-") {
			if (posixEndDateTime >= posixNowDateTime) {
				outputBox->Rows[index-1]->Cells[OutputBoxColumn::END]->Style->BackColor = Color::Lime;
			} else {
				outputBox->Rows[index-1]->Cells[OutputBoxColumn::END]->Style->BackColor = Color::Red;
				outputBox->Rows[index-1]->Cells[OutputBoxColumn::START]->Style->BackColor = Color::Red;
			}
		}

		// TODO: Refactor this section to formatOutputBoxDoneColumn(...);
		if (isCompleted) {
			outputBox->Rows[index-1]->Cells[OutputBoxColumn::DONE]->Style->BackColor = Color::Lime;
		} else {
			outputBox->Rows[index-1]->Cells[OutputBoxColumn::DONE]->Style->BackColor = Color::Red;
		}


		// For formatting colours of header in outputBox. Not implementing now because it looks worse.
		//Color headerBack = System::Drawing::ColorTranslator::FromHtml("#3F51B5");
		//Color headerFore = System::Drawing::ColorTranslator::FromHtml("#E8EAF6");

		//DataGridViewCellStyle^ headerStyle = outputBox->ColumnHeadersDefaultCellStyle;
		//headerStyle->Font = gcnew System::Drawing::Font(outputBox->Font, FontStyle::Bold);
		//outputBox->AdjustColumnHeaderBorderStyle;

		//outputBox->ColumnHeadersDefaultCellStyle->BackColor = headerBack;
		//outputBox->ColumnHeadersDefaultCellStyle->ForeColor = headerFore;
		//outputBox->GridColor = headerBack;
		//outputBox->EnableHeadersVisualStyles = false;
		// number->HeaderCell->Style->BackColor = Color::Blue;
		// outputBox->RowHeadersDefaultCellStyle->ForeColor = Color::Red;

		delete num;
		delete taskText;
		delete start;
		delete end;
		delete tags;
		delete done;
	}
	return;
}
