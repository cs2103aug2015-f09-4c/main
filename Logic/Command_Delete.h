#pragma once
#include "Command.h"

//Feedback message for different delete operation result
const std::string MESSAGE_DELETE_INDEX_SUCCESS = "Task at index %i have been deleted successfully.";
const std::string MESSAGE_DELETE_INDEX_FAIL = "No task is found at index %i.";

class DeleteCommand: public Command{
public:
	DeleteCommand (SecondaryCommandType type2);
	virtual UIFeedback Command::execute(StorageHandler* storageHandler) = 0;
	bool isValid();
};

class IndexDeleteCommand: public DeleteCommand{
private:
	size_t _index;
	Task _taskDeleted;
public:
	IndexDeleteCommand(size_t index);
	UIFeedback DeleteCommand::execute(StorageHandler* storageHandler);
	virtual ~IndexDeleteCommand();
};

