#include "Command_Edit.h"

EditCommand::EditCommand(SecondaryCommandType type2, size_t index) : Command(PrimaryCommandType::Edit) {
	_type2 = type2;
	_index = index;
}

bool EditCommand::canUndo() {
	return true;
}

EditNameCommand::EditNameCommand(size_t index, std::string newTaskText):EditCommand(SecondaryCommandType::Name, index) {
	_newTaskText = newTaskText;
}

UIFeedback EditNameCommand::execute(StorageHandler* storageHandler) {
	std::string feedbackMessage;
	
	if (_newTaskText.size() < 1) {
		feedbackMessage = MESSAGE_EDIT_NAME_EMPTY;
	} else {
		Task& taskToEdit = storageHandler -> find(_index);
		_oldTaskText = taskToEdit.getTaskText();
		taskToEdit.changeTaskText(_newTaskText);
		char buffer[255];
		sprintf_s(buffer, MESSAGE_EDIT_NAME_SUCCESS.c_str(), _oldTaskText.c_str(), _newTaskText.c_str());
		feedbackMessage = std::string(buffer);
		_statusExecuted = true;
	}
	UIFeedback feedback(storageHandler->getTasksToDisplay(), feedbackMessage);
	return feedback;
}

UIFeedback EditNameCommand::undo() {
	//TODO
	return UIFeedback();
}

EditStartCommand::EditStartCommand(size_t index, boost::posix_time::ptime newStart) : EditCommand(SecondaryCommandType::Start, index) {
	_newStart = newStart;
}

UIFeedback EditStartCommand::execute(StorageHandler* storageHandler) {
	std::string feedbackMessage;
	
	Task& taskToEdit = storageHandler -> find(_index);
	_oldStart = taskToEdit.getStartDateTime();
	taskToEdit.changeStartDateTime(_newStart);
	
	char buffer[255];
	std::string newStartString = boost::posix_time::to_simple_string(_newStart);
	sprintf_s(buffer, MESSAGE_EDIT_START_SUCCESS.c_str(), taskToEdit.getTaskText().c_str(), newStartString.c_str());
	feedbackMessage = std::string(buffer);
	
	_statusExecuted = true;
	
	UIFeedback feedback(storageHandler->getTasksToDisplay(), feedbackMessage);
	return feedback;
}

UIFeedback EditStartCommand::undo() {
	//TODO
	return UIFeedback();
}

EditEndCommand::EditEndCommand(size_t index, boost::posix_time::ptime newEnd) : EditCommand(SecondaryCommandType::End, index) {
	_newEnd = newEnd;
}

UIFeedback EditEndCommand::execute(StorageHandler* storageHandler) {
	std::string feedbackMessage;
	
	Task& taskToEdit = storageHandler -> find(_index);
	_oldEnd = taskToEdit.getEndDateTime();
	taskToEdit.changeEndDateTime(_newEnd);
	
	char buffer[255];
	std::string newEndString = boost::posix_time::to_simple_string(_newEnd);
	sprintf_s(buffer, MESSAGE_EDIT_END_SUCCESS.c_str(), taskToEdit.getTaskText().c_str(), newEndString.c_str());
	feedbackMessage = std::string(buffer);
	
	_statusExecuted = true;
	
	UIFeedback feedback(storageHandler->getTasksToDisplay(), feedbackMessage);
	return feedback;
}

UIFeedback EditEndCommand::undo() {
	//TODO
	return UIFeedback();
}