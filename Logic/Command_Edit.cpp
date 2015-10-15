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

UIFeedback EditNameCommand::execute(RunTimeStorage* runTimeStorage) {
	std::string feedbackMessage;

	assert (!_newTaskText.empty());

	try {
		Task& taskToEdit = runTimeStorage -> find(_index);
		_editIndex = runTimeStorage -> find(taskToEdit);
		_oldTaskText = taskToEdit.getTaskText();
		taskToEdit.changeTaskText(_newTaskText);

		char buffer[255];
		sprintf_s(buffer, MESSAGE_EDIT_NAME_SUCCESS.c_str(), _oldTaskText.c_str(), _newTaskText.c_str());
		feedbackMessage = std::string(buffer);

		_statusExecuted = true;
		_runTimeStorageExecuted = runTimeStorage;
		return UIFeedback(runTimeStorage->getTasksToDisplay(), feedbackMessage);
	} catch (std::exception e){
		feedbackMessage = e.what();
		return UIFeedback(runTimeStorage->getTasksToDisplay(), feedbackMessage);
	}
}

UIFeedback EditNameCommand::undo() {
	assert(_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);

	Task& taskToEdit = _runTimeStorageExecuted->getEntry(_editIndex);

	taskToEdit.changeTaskText(_oldTaskText);

	_statusExecuted = false;
	std::vector<Task> taskToDisplay = _runTimeStorageExecuted->getTasksToDisplay();
	_runTimeStorageExecuted = NULL;

	return UIFeedback(taskToDisplay, MESSAGE_EDIT_UNDO);
}

EditStartCommand::EditStartCommand(size_t index, boost::posix_time::ptime newStart) : EditCommand(SecondaryCommandType::Start, index) {
	_newStart = newStart;
}

UIFeedback EditStartCommand::execute(RunTimeStorage* runTimeStorage) {
	std::string feedbackMessage;

	try {
		Task& taskToEdit = runTimeStorage -> find(_index);
		_editIndex = runTimeStorage -> find(taskToEdit);
		_oldStart = taskToEdit.getStartDateTime();
		taskToEdit.changeStartDateTime(_newStart);

		char buffer[255];
		std::string newStartString = boost::posix_time::to_simple_string(_newStart);
		sprintf_s(buffer, MESSAGE_EDIT_START_SUCCESS.c_str(), taskToEdit.getTaskText().c_str(), newStartString.c_str());
		feedbackMessage = std::string(buffer);

		_statusExecuted = true;
		_runTimeStorageExecuted = runTimeStorage;
		return UIFeedback(runTimeStorage->getTasksToDisplay(), feedbackMessage);
	} catch (std::exception e) {
		feedbackMessage = e.what();
		return UIFeedback(runTimeStorage->getTasksToDisplay(), feedbackMessage);
	}
}

UIFeedback EditStartCommand::undo() {
	//TODO
	return UIFeedback();
}

EditEndCommand::EditEndCommand(size_t index, boost::posix_time::ptime newEnd) : EditCommand(SecondaryCommandType::End, index) {
	_newEnd = newEnd;
}

UIFeedback EditEndCommand::execute(RunTimeStorage* runTimeStorage) {
	std::string feedbackMessage;
	try {
		Task& taskToEdit = runTimeStorage -> find(_index);
		_editIndex = runTimeStorage -> find(taskToEdit);
		_oldEnd = taskToEdit.getEndDateTime();
		taskToEdit.changeEndDateTime(_newEnd);

		char buffer[255];
		std::string newEndString = boost::posix_time::to_simple_string(_newEnd);
		sprintf_s(buffer, MESSAGE_EDIT_END_SUCCESS.c_str(), taskToEdit.getTaskText().c_str(), newEndString.c_str());
		feedbackMessage = std::string(buffer);

		_statusExecuted = true;
		_runTimeStorageExecuted = runTimeStorage;

		return UIFeedback(runTimeStorage->getTasksToDisplay(), feedbackMessage);
	} catch(std::exception e) {
		feedbackMessage = e.what();
		return UIFeedback(runTimeStorage->getTasksToDisplay(), feedbackMessage);
	}
}

UIFeedback EditEndCommand::undo() {
	//TODO
	return UIFeedback();
}