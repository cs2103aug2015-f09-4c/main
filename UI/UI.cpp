//@@author A0124439E
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

std::string UI::Swiftask::getStdStringCommand(void) {
	System::String^ managed;

	managed = commandBox->Text;
	commandBox->Text = "";

	return msclr::interop::marshal_as<std::string>(managed);
}

void UI::Swiftask::updateUI(void) {
	updateResults();

	clearOutputBox();
	displayInOutputBox();

	return;
}

void UI::Swiftask::updateResults(void) {

	System::String^ managed = gcnew String((*feedback).getFeedbackMessage().c_str());
	results->Text = managed;
	delete managed;

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
	int rowIndex = 0;
	bool isCompleted = false;
	std::ostringstream convert;

	for (std::vector<API::Task>::iterator it = (*feedback).getTasksForDisplay().begin(); it < (*feedback).getTasksForDisplay().end(); it++) {
		convert << (rowIndex + 1);
		num = gcnew String(convert.str().c_str());
		convert.str(std::string());

		taskText = gcnew String((*it).getTaskText().c_str());

		posixStartDateTime = (*it).getStartDateTime();

		posixEndDateTime = (*it).getEndDateTime();

		std::set<std::string> tagsList;
		tagsList = (*it).getTags();

		isCompleted = (*it).isComplete();

		if (!posixStartDateTime.is_not_a_date_time()) {
			startDateTime = gcnew String(boost::posix_time::to_simple_string(posixStartDateTime).c_str());

		} else {
			startDateTime = gcnew String("-");
		}

		if (!posixEndDateTime.is_not_a_date_time()) {
			endDateTime = gcnew String(boost::posix_time::to_simple_string(posixEndDateTime).c_str());
		} else {
			endDateTime = gcnew String("-");
		}


		std::string stdTags = "";
		if (tagsList.size() != 0) {
			for (std::set<std::string>::iterator iter = tagsList.begin(); iter != tagsList.end(); iter++) {
				stdTags = stdTags + " " + (*iter);
			}
			theTags = gcnew String(stdTags.c_str());
		} else {
			theTags = gcnew String("-");
		}

		outputBox->Rows->Add(num, taskText, startDateTime, endDateTime, theTags);

		formatOutputBox(isCompleted, timePast(posixStartDateTime), timePast(posixEndDateTime), rowIndex);

		rowIndex++;

		delete num;
		delete taskText;
		delete start;
		delete end;
		delete tags;
		delete done;
	}
	return;
}

void UI::Swiftask::formatOutputBoxInitial() {
	Color colHeaderBack = System::Drawing::ColorTranslator::FromHtml("#3F51B5");	// Indigo500
	Color colHeaderFore = System::Drawing::ColorTranslator::FromHtml("#E8EAF6");	// Indigo50
	Color rowHeaderBack = System::Drawing::ColorTranslator::FromHtml("#9FA8DA");	// Indigo200

	outputBox->ColumnHeadersDefaultCellStyle->BackColor = colHeaderBack;
	outputBox->ColumnHeadersDefaultCellStyle->ForeColor = colHeaderFore;

	DataGridViewCellStyle^ colHeaderStyle = outputBox->ColumnHeadersDefaultCellStyle;
	colHeaderStyle->Font = gcnew System::Drawing::Font(outputBox->Font, FontStyle::Bold);

	outputBox->RowHeadersDefaultCellStyle->BackColor = rowHeaderBack;

	//outputBox->GridColor = colHeaderFore;

	outputBox->EnableHeadersVisualStyles = false;
	return;
}

void UI::Swiftask::formatOutputBox(bool isCompleted, dateTimeStat start, dateTimeStat end, int rowIndex) {

	if (0 > rowIndex || outputBox->RowCount <= rowIndex) {
		logger->logDEBUG("rowIndex given out of bounds");
		return;
	}

	formatOutputBoxRow(rowIndex);
	formatOutputBoxStartEndColumn(isCompleted, start, end, rowIndex);
	formatOutputBoxDoneColumn(isCompleted, rowIndex);

	return;
}

void UI::Swiftask::formatOutputBoxRow(int rowIndex) {
	Color oddRow = System::Drawing::ColorTranslator::FromHtml("#E8EAF6");	// Indigo50
	Color evenRow = System::Drawing::ColorTranslator::FromHtml("#C5CAE9");	// Indigo100

	DataGridViewCellStyle^ rowHeaderStyle = outputBox->RowHeadersDefaultCellStyle;

	if (rowIndex % 2) {
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::NUM]->Style->BackColor = oddRow;
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::TASKTEXT]->Style->BackColor = oddRow;
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::START]->Style->BackColor = oddRow;
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::END]->Style->BackColor = oddRow;
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::TAGS]->Style->BackColor = oddRow;
	} else {
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::NUM]->Style->BackColor = evenRow;
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::TASKTEXT]->Style->BackColor = evenRow;
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::START]->Style->BackColor = evenRow;
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::END]->Style->BackColor = evenRow;
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::TAGS]->Style->BackColor = evenRow;
	}

	return;
}

void UI::Swiftask::formatOutputBoxStartEndColumn(bool isCompleted, dateTimeStat start, dateTimeStat end, int rowIndex) {
	Color green = System::Drawing::ColorTranslator::FromHtml("#4CAF50");	// Green500
	Color red = System::Drawing::ColorTranslator::FromHtml("#E57373");		// Red300

	boost::posix_time::ptime posixNowDateTime;
	posixNowDateTime = boost::posix_time::second_clock::local_time();

	if (!isCompleted && !end.isNotDateTime) {
		if (end.hasPast) {
			outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::END]->Style->BackColor = red;
			if (!start.isNotDateTime) {
				outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::START]->Style->BackColor = red;
			}
		} else if (start.hasPast) {
			outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::START]->Style->BackColor = green;
			outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::END]->Style->BackColor = green;
		}
	}

	return;
}

void UI::Swiftask::formatOutputBoxDoneColumn(bool isCompleted, int rowIndex) {
	Color green = System::Drawing::ColorTranslator::FromHtml("#4CAF50");	// Green500
	Color red = System::Drawing::ColorTranslator::FromHtml("#E57373");		// Red300

	if (isCompleted) {
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::DONE]->Style->BackColor = green;
	} else {
		outputBox->Rows[rowIndex]->Cells[OutputBoxColumn::DONE]->Style->BackColor = red;
	}

	return;
}

UI::dateTimeStat UI::Swiftask::timePast(boost::posix_time::ptime posixDateTime) {
	dateTimeStat dateTime;

	if (posixDateTime.is_not_a_date_time()) {
		dateTime.isNotDateTime = true;
		dateTime.hasPast = false;		// Just to give it a value
	} else {
		dateTime.isNotDateTime = false;

		boost::posix_time::ptime posixNowDateTime;
		posixNowDateTime = boost::posix_time::second_clock::local_time();

		if (posixDateTime <= posixNowDateTime) {
			dateTime.hasPast = true;
		} else {
			dateTime.hasPast = false;
		}
	}

	return dateTime;
}
