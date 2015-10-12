#pragma once

#include "Command.h"

//Undo command does not holds any functionality by itself. 
//The only purpose of this sub class is to allow user to know that undo of previous executed command need to be called.

class UndoCommand: public Command {
public:
	UndoCommand(void);
	UIFeedback Command::execute(RunTimeStorage*);
	UIFeedback Command::undo(void);
	bool Command::canUndo(void);
	virtual ~UndoCommand(void);
};

