#ifndef COMMAND_H_
#define COMMAND_H_

#include "StorageHandler.h"
using namespace API;

//Feedback message for invalid command type
const std::string MESSAGE_INVALID = "Invalid command line. Please key in another command";

//Feedback message for different add operation result
const std::string MESSAGE_ADD_SUCCESS = "\"%s\" have been added succesfully.\nStart Date Time: %s\nEnd Date Time: %s"; 
const std::string MESSAGE_ADD_EMPTY = "Task text cannot be empty.";
const std::string MESSAGE_ADD_DUPLICATE = "Duplicate task is found. New task is not added.";

//Feedback message for different delete operation result
const std::string MESSAGE_DELETE_INDEX_SUCCESS = "Task at index %i have been deleted successfully.";
const std::string MESSAGE_DELETE_INDEX_FAIL = "No task is found at index %i.";

class Command {
protected:
	PrimaryCommandType _type1;
	SecondaryCommandType _type2;
public:
	Command(PrimaryCommandType type);
	PrimaryCommandType getPrimaryCommandType();
	SecondaryCommandType getSecondaryCommandType();
	bool isValid();
	virtual UIFeedback execute(StorageHandler* a) = 0;
};

class InvalidCommand: public Command {
public:
	InvalidCommand ();
	UIFeedback execute(StorageHandler* storageHandler);
};

class AddCommand: public Command {
private:
	Task _task;
public:
	AddCommand (SecondaryCommandType type2, Task task);
	UIFeedback execute(StorageHandler* storageHandler);
	bool isValid();
	Task getTask();
};

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
};

class InvalidDeleteCommand: public DeleteCommand {
public:
	InvalidDeleteCommand();
	UIFeedback DeleteCommand::execute(StorageHandler* storageHandler);
};


#endif