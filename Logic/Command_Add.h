#pragma once
#include "Command.h"

//Feedback message for different add operation result
const std::string MESSAGE_ADD_SUCCESS = "\"%s\" have been added succesfully.\nStart Date Time: %s\nEnd Date Time: %s"; 
const std::string MESSAGE_ADD_EMPTY = "Task text cannot be empty. New task is not added.";
const std::string MESSAGE_ADD_DUPLICATE = "Duplicate task is found. New task is not added.";

class AddCommand: public Command {
private:
	Task _task;
public:
	AddCommand (SecondaryCommandType type2, Task task);
	UIFeedback execute(StorageHandler* storageHandler);
	UIFeedback undo(void);

	bool canUndo();

	virtual ~AddCommand(void);
};