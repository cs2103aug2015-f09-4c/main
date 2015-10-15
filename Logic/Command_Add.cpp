#include "Command_Add.h"

AddCommand::AddCommand (SecondaryCommandType type2, Task task) : Command(PrimaryCommandType::Add) {
	_type2 = type2;
	_task = task;
}

UIFeedback AddCommand::execute(RunTimeStorage* runTimeStorage) {
	UIFeedback feedback;
	if (_task.getTaskText().size() < 1) {
		feedback = UIFeedback(runTimeStorage->getTasksToDisplay(), MESSAGE_ADD_EMPTY);
	} else if (runTimeStorage->isDuplicate(_task)) {
		feedback = UIFeedback(runTimeStorage->getTasksToDisplay(), MESSAGE_ADD_DUPLICATE);
	} else {
		runTimeStorage->add(_task);
		std::string taskText = _task.getTaskText();
		std::string startDateTime = boost::posix_time::to_simple_string(_task.getStartDateTime());
		std::string endDateTime = boost::posix_time::to_simple_string(_task.getEndDateTime());
		char buffer[255];
		sprintf_s(buffer, MESSAGE_ADD_SUCCESS.c_str(), taskText.c_str(), startDateTime.c_str(), endDateTime.c_str());
		std::string feedbackMessage(buffer);
		feedback = UIFeedback(runTimeStorage->getTasksToDisplay(), feedbackMessage);
		_statusExecuted = true;
		_runTimeStorageExecuted = runTimeStorage;
	}
	return feedback;
}

UIFeedback AddCommand::undo() {
	assert (_statusExecuted);
	assert(_runTimeStorageExecuted != NULL);
	_runTimeStorageExecuted -> removeLastEntry();
	std::vector<Task>& tasksToDisplay = _runTimeStorageExecuted->getTasksToDisplay();
	_runTimeStorageExecuted = NULL;
	return UIFeedback(tasksToDisplay, MESSAGE_UNDO_ADD);
}

bool AddCommand::canUndo() {
	return true;
}

AddCommand::~AddCommand(void) {	
}