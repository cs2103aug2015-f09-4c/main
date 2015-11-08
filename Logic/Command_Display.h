//@@author A0112218W
#pragma once
#include "Command.h"

const std::string MESSAGE_DISPLAY_SUCCESS = "Display mode have been changed successfully.";
const std::string MESSAGE_DISPLAY_UNDO = "Display mode have been changed back successfully";

/**
 *	Command sub class responsible for changing display mode
 */
class DisplayCommand : public Command {
private:
	/**
	 *	Display_Type to change to
	 */
	Display_Type _newDisplayType;

	/**
	 *	Original Display_Type, used for undo
	 */
	Display_Type _oldDisplayType;
public:
	/**
	 *	Constructor
	 *	@param displayType Display_Type to change to
	 */
	DisplayCommand(Display_Type displayType);

	/**
	 *	Execution method of DisplayCommand.
	 *	Change display mode of the program.
	 */
	UIFeedback Command::execute(RunTimeStorage*);

	/**
	 *	Undo method of DisplayCommand.
	 *	Revert display mode back to the previous one.
	 */
	UIFeedback Command::undo();

	/**
	 *	Return true all the time.
	 */
	bool canUndo();

	/**
	 *	Destructor
	 */
	virtual ~DisplayCommand(void);
};