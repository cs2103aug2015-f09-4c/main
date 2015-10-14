#pragma once
#include "Command.h"

//Feedback message for invalid command type
const std::string MESSAGE_INVALID_COMMAND = "Invalid Command. No change is made.";

class InvalidCommand: public Command {
private:
	//to specify the reason it is invalid
	std::string _message; 
public:
	InvalidCommand (void);
	InvalidCommand (std::string _message);
	UIFeedback execute(RunTimeStorage*);
	UIFeedback undo();
	bool canUndo();
};

