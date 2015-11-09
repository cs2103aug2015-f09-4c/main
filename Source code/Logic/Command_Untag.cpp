//@@author A0112218W

#include "Command_Untag.h"

UntagCommand::UntagCommand(size_t index, std::vector<std::string> untags) : Command(CommandTokens::Untag) {
	_index = index;
	_untags = untags;
	_type2 = CommandTokens::Index;
}

UIFeedback UntagCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	std::string feedbackMessage;
	try {
		Task& taskToUntag = runTimeStorage->find(_index);
		_untagIndex = runTimeStorage->find(taskToUntag);
		for (size_t i = 0 ; i < _untags.size() ; ++i) {
			try {
				taskToUntag.removeTag(_untags[i]);
				_successUntags.push_back(_untags[i]);
			} catch (TASK_EXCEPTION e){
				feedbackMessage += std::string(e.what());
				feedbackMessage += "\n";
			}
		}
	} catch (INDEX_NOT_FOUND_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	} catch (TASK_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	}

	if (_successUntags.size() > 0) {
		postExecutionAction(runTimeStorage);
		char buffer[255];
		sprintf_s(buffer, MESSAGE_UNTAG_SUCCESS.c_str(), _index, _successUntags.size());
		feedbackMessage += std::string(buffer);
	}

	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), feedbackMessage);	
}
UIFeedback UntagCommand::undo() {
	checkIsValidForUndo();
	Task& taskToUntag = _runTimeStorageExecuted->getEntry(_untagIndex);
	for (size_t i = 0 ; i < _successUntags.size() ; ++i) {
		taskToUntag.addTag(_successUntags[i]);
	}
	std::vector<Task> tasksToDisplay = _runTimeStorageExecuted->refreshTasksToDisplay();
	postUndoAction();

	return UIFeedback(tasksToDisplay, MESSAGE_UNTAG_UNDO);	
}

bool UntagCommand::canUndo() {
	return true;
}

UntagCommand::~UntagCommand(void)
{
}
