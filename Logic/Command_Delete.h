#pragma once
#include "Command.h"

//Feedback message for different delete operation result
const std::string MESSAGE_DELETE_INDEX_SUCCESS = "Task at index %i have been deleted successfully.";
const std::string MESSAGE_DELETE_INDEX_FAIL = "No task is found at index %i.";

const std::string MESSAGE_DELETE_UNDO = "Previous delete operation is undoed.";

class DeleteCommand: public Command{
public:
	DeleteCommand (SecondaryCommandType type2);
	virtual UIFeedback Command::execute(RunTimeStorage*) = 0;
	virtual UIFeedback Command::undo() = 0;

	bool isValid();
	bool canUndo();
};

class IndexDeleteCommand: public DeleteCommand{
private:
	size_t _index;
	Task _taskDeleted;
	size_t _entryIndex;
public:
	IndexDeleteCommand(size_t index);
	UIFeedback DeleteCommand::execute(RunTimeStorage*);
	UIFeedback DeleteCommand::undo(void);
	virtual ~IndexDeleteCommand();
};

