//@@author A0112218W
#pragma once
#include "Command.h"

const std::string MESSAGE_DISPLAY_SUCCESS = "Display mode have been changed successfully.";
const std::string MESSAGE_DISPLAY_UNDO = "Display mode have been changed back successfully";

class DisplayCommand : public Command {
private:
	Display_Type _newDisplayType;
	Display_Type _oldDisplayType;
public:
	DisplayCommand(Display_Type);
	UIFeedback Command::execute(RunTimeStorage*);
	UIFeedback Command::undo();
	bool canUndo();
	virtual ~DisplayCommand(void);
};