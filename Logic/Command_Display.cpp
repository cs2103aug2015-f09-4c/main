//@@author A0112218W

#include "Command_Display.h"

DisplayCommand::DisplayCommand(Display_Type type) : Command (CommandTokens::PrimaryCommandType::Display){
	_newDisplayType = type;
}

UIFeedback DisplayCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	_oldDisplayType = runTimeStorage->getDisplayType();
	runTimeStorage->changeDisplayType(_newDisplayType);
	
	postExecutionAction(runTimeStorage);

	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), MESSAGE_DISPLAY_SUCCESS); 
}

UIFeedback DisplayCommand::undo() {
	checkIsValidForUndo();
	_runTimeStorageExecuted->changeDisplayType(_oldDisplayType);

	std::vector<Task> tasksToDisplay = _runTimeStorageExecuted->refreshTasksToDisplay();

	postUndoAction();

	return UIFeedback(tasksToDisplay, MESSAGE_DISPLAY_UNDO);
}

bool DisplayCommand::canUndo() {
	return true;
}

DisplayCommand::~DisplayCommand(void) {
}
