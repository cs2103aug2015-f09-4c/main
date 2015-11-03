//@@author A0112218W

#include "Command_Display.h"

DisplayCommand::DisplayCommand(Display_Type type) : Command (CommandTokens::PrimaryCommandType::Display){
	_newDisplayType = type;
}

UIFeedback DisplayCommand::execute(RunTimeStorage* runTimeStorage) {
	assert(runTimeStorage != NULL);
	assert(!_statusExecuted);
	_oldDisplayType = runTimeStorage->getDisplayType();
	runTimeStorage->changeDisplayType(_newDisplayType);
	
	_runTimeStorageExecuted = runTimeStorage;
	_statusExecuted = true;

	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), MESSAGE_DISPLAY_SUCCESS); 
}

UIFeedback DisplayCommand::undo() {
	assert(_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	_runTimeStorageExecuted->changeDisplayType(_oldDisplayType);

	std::vector<Task> tasksToDisplay = _runTimeStorageExecuted->refreshTasksToDisplay();

	_runTimeStorageExecuted = NULL;
	_statusExecuted = false;

	return UIFeedback(tasksToDisplay, MESSAGE_DISPLAY_UNDO);
}

bool DisplayCommand::canUndo() {
	return true;
}

DisplayCommand::~DisplayCommand(void) {
}
