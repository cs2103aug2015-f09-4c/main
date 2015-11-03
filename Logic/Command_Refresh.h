//@@author A0112218W
#pragma once

#include "Command.h"

class RefreshCommand : public Command {
public:
	RefreshCommand(void);
	bool Command::canUndo() {
		return false;
	}

	UIFeedback execute(RunTimeStorage*);
	UIFeedback undo();
	~RefreshCommand(void);
};

