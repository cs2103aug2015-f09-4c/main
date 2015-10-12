#include "Command_Undo.h"

UndoCommand::UndoCommand(void): Command(PrimaryCommandType::Undo) {
	_type2 = SecondaryCommandType::None;
}

UIFeedback UndoCommand::execute(RunTimeStorage*) {
	//to ensure this method is never called.
	assert(false);
	
	return UIFeedback();
}
UIFeedback UndoCommand::undo(void) {
	//to ensure this method is never called.
	assert(false);

	return UIFeedback();
}

bool UndoCommand::canUndo(void) {
	return true;
}

UndoCommand::~UndoCommand(void) {
}
