#pragma once
#include "Command.h"

//Feedback message for different add operation result
const std::string MESSAGE_ADD_SUCCESS = "\"%s\" have been added succesfully.\nStart Date Time: %s\nEnd Date Time: %s"; 
const std::string MESSAGE_ADD_EMPTY = "Task text cannot be empty. New task is not added.";


//Feedback message when add operation is undoed
const std::string MESSAGE_UNDO_ADD = "Previous add operation is undoed succesfully";

class AddCommand: public Command {
private:
	Task _task;
public:
	AddCommand (CommandTokens::SecondaryCommandType type2, Task task);
	UIFeedback execute(RunTimeStorage*);
	UIFeedback undo(void);

	bool canUndo();

	virtual ~AddCommand(void);
};