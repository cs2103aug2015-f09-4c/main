//@@author A0112218W

#include "Command_Sort.h"

SortCommand::SortCommand(Sort_Type type) : Command (CommandTokens::PrimaryCommandType::Sort){
	_newSortType = type;
}

UIFeedback SortCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	_oldSortType = runTimeStorage->getSortType();
	runTimeStorage->changeSortType(_newSortType);
	postExecutionAction(runTimeStorage);

	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), MESSAGE_SORT_SUCCESS); 
}

UIFeedback SortCommand::undo() {
	checkIsValidForUndo();
	_runTimeStorageExecuted->changeSortType(_oldSortType);

	std::vector<Task> tasksToDisplay = _runTimeStorageExecuted->refreshTasksToDisplay();

	postUndoAction();

	return UIFeedback(tasksToDisplay, MESSAGE_SORT_UNDO);
}

bool SortCommand::canUndo() {
	return true;
}

SortCommand::~SortCommand(void) {
}
