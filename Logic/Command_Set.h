#pragma once
#include "Command.h"

//Feedback message for set complete operation
const std::string MESSAGE_SET_COMPLETE_SUCCESS = "Task at index %i have been set to complete.";
const std::string MESSAGE_SET_COMPLETE_NO_CHANGE = "Task at index %i is already complete, no change is made.";
const std::string MESSAGE_SET_COMPLETE_FAIL = "No task is found at index %i.";

class SetCompleteCommand: public Command {
private:
	size_t _index;
public:
	SetCompleteCommand(size_t index);
	UIFeedback Command::execute(StorageHandler*);
	UIFeedback Command::undo();
	bool canUndo();
};

