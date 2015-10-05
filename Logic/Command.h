#ifndef COMMAND_H_
#define COMMAND_H_

#include "StorageHandler.h"
using namespace API;

//Feedback message for invalid command type
const std::string MESSAGE_INVALID_COMMAND = "Invalid Command. No change is made.";

//Feedback message for different add operation result
const std::string MESSAGE_ADD_SUCCESS = "\"%s\" have been added succesfully.\nStart Date Time: %s\nEnd Date Time: %s"; 
const std::string MESSAGE_ADD_EMPTY = "Task text cannot be empty. New task is not added.";
const std::string MESSAGE_ADD_DUPLICATE = "Duplicate task is found. New task is not added.";

//Feedback message for different delete operation result
const std::string MESSAGE_DELETE_INDEX_SUCCESS = "Task at index %i have been deleted successfully.";
const std::string MESSAGE_DELETE_INDEX_FAIL = "No task is found at index %i.";

//Feedback message for different edit operation result
const std::string MESSAGE_EDIT_NAME_SUCCESS = "Task \"%s\"'s task text have been changed to \"%s\".";
const std::string MESSAGE_EDIT_NAME_EMPTY = "Task text cannot be empty. Task text is not changed.";

class Command {
protected:
	PrimaryCommandType _type1;
	SecondaryCommandType _type2;
	bool _statusExecuted;
public:
	Command(PrimaryCommandType type);
	PrimaryCommandType getPrimaryCommandType();
	SecondaryCommandType getSecondaryCommandType();
	bool isValid();
	bool isExecutedSuccessfully();
	virtual UIFeedback execute(StorageHandler* a) = 0;
	~Command() {}
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

class EditCommand: public Command {
protected:
	size_t _index;
public:
	EditCommand(SecondaryCommandType, size_t);
	virtual UIFeedback Command::execute(StorageHandler* storageHandler) = 0;
};

class EditNameCommand: public EditCommand {
private:
	std::string _newTaskText;
	std::string _oldTaskText; //for undo later
public:
	EditNameCommand(size_t index, std::string newTaskText);
	UIFeedback EditCommand::execute(StorageHandler*);
};
#endif