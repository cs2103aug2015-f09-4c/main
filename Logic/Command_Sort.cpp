//@@author A0112218W

#include "Command_Sort.h"

SortCommand::SortCommand(Sort_Type type) : Command (CommandTokens::PrimaryCommandType::Sort){
	_newSortType = type;
}

UIFeedback SortCommand::execute(RunTimeStorage* runTimeStorage) {
	assert(runTimeStorage != NULL);
	assert(!_statusExecuted);
	_oldSortType = runTimeStorage->getSortType();
	runTimeStorage->changeSortType(_newSortType);
	
	_runTimeStorageExecuted = runTimeStorage;
	_statusExecuted = true;

	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), MESSAGE_SORT_SUCCESS); 
}

UIFeedback SortCommand::undo() {
	assert(_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	_runTimeStorageExecuted->changeSortType(_oldSortType);

	std::vector<Task> tasksToDisplay = _runTimeStorageExecuted->refreshTasksToDisplay();

	_runTimeStorageExecuted = NULL;
	_statusExecuted = false;

	return UIFeedback(tasksToDisplay, MESSAGE_SORT_UNDO);
}

bool SortCommand::canUndo() {
	return true;
}

SortCommand::~SortCommand(void) {
}
