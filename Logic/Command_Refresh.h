//@@author A0112218W
#pragma once

#include "Command.h"

/**
 *	Command sub class responsible to refresh display on UI
 */
class RefreshCommand : public Command {
public:
	/**
	 *	Constructor
	 */
	RefreshCommand(void);

	/**
	 *	Return false all the time
	 */
	bool Command::canUndo() {
		return false;
	}

	/**
	 *	Execution method of RefreshCommand.
	 *	Refresh display on UI.
	 */
	UIFeedback execute(RunTimeStorage*);
	UIFeedback undo();

	/**
	 *	Destructor.
	 */
	~RefreshCommand(void);
};

