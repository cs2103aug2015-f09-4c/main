//@@author A0112218W

#include "Command_Add.h"

AddCommand::AddCommand (CommandTokens::SecondaryCommandType type2, Task task) : Command(CommandTokens::PrimaryCommandType::Add) {
	_type2 = type2;
	_task = task;
}

UIFeedback AddCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);

	UIFeedback feedback;
	try {
		runTimeStorage->add(_task);
		std::string taskText = _task.getTaskText();
		std::string startDateTime = boost::posix_time::to_simple_string(_task.getStartDateTime());
		std::string endDateTime = boost::posix_time::to_simple_string(_task.getEndDateTime());
		char buffer[255];
		sprintf_s(buffer, MESSAGE_ADD_SUCCESS.c_str(), taskText.c_str(), startDateTime.c_str(), endDateTime.c_str());
		std::string feedbackMessage(buffer);
		feedback = UIFeedback(runTimeStorage->refreshTasksToDisplay(), feedbackMessage);
		postExecutionAction(runTimeStorage);
	} catch (DUPLICATE_TASK_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	}
	return feedback;
}

UIFeedback AddCommand::undo() {
	checkIsValidForUndo();
	_runTimeStorageExecuted -> removeLastEntry();
	std::vector<Task>& tasksToDisplay = _runTimeStorageExecuted->refreshTasksToDisplay();
	postUndoAction();
	return UIFeedback(tasksToDisplay, MESSAGE_UNDO_ADD);
}

bool AddCommand::canUndo() {
	return true;
}

AddCommand::~AddCommand(void) {	
}