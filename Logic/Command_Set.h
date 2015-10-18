#pragma once
#include "Command.h"

//Feedback message for set complete operation
const std::string MESSAGE_SET_COMPLETE_SUCCESS = "Task at index %i have been set to complete.";
const std::string MESSAGE_SET_COMPLETE_NO_CHANGE = "Task at index %i is already complete, no change is made.";
const std::string MESSAGE_SET_COMPLETE_FAIL = "No task is found at index %i.";

const std::string MESSAGE_SET_UNDO = "Task's complete status have been reverted.";

class ALREADY_COMPLETE_EXCEPTION : public std::exception {
private:
	char _message[255];
public:
	explicit ALREADY_COMPLETE_EXCEPTION(int index);

	const char* what(void) const throw();
};

class SetCompleteCommand: public Command {
private:
	size_t _index;
	size_t _setIndex;
public:
	SetCompleteCommand(size_t index);
	UIFeedback Command::execute(RunTimeStorage*);
	UIFeedback Command::undo();
	bool canUndo();
};

