#pragma once
#include "Command.h"

//Feedback message for different delete operation result
const std::string MESSAGE_DELETE_INDEX_SUCCESS = "Task at index %i have been deleted successfully.";
const std::string MESSAGE_DELETE_ALL_SUCCESS = "All tasks have been removed.";
const std::string MESSAGE_DELETE_BEFORE_SUCCESS = "All tasks ended before %s have been removed.";

const std::string MESSAGE_DELETE_UNDO = "Previous delete operation is undoed.";

class DeleteCommand: public Command{
public:
	DeleteCommand (CommandTokens::SecondaryCommandType type2);
	virtual UIFeedback Command::execute(RunTimeStorage*) = 0;
	virtual UIFeedback Command::undo() = 0;

	bool isValid();
	bool canUndo();
};

class DeleteIndexCommand: public DeleteCommand{
private:
	size_t _index;
	Task _taskDeleted;
	size_t _entryIndex;
public:
	DeleteIndexCommand(size_t index);
	UIFeedback DeleteCommand::execute(RunTimeStorage*);
	UIFeedback DeleteCommand::undo(void);
	virtual ~DeleteIndexCommand();
};

class DeleteBeforeCommand: public DeleteCommand{
private:
	std::vector<Task> _tasksDeleted;
	std::vector<int> _indexTaskDeleted;
	boost::posix_time::ptime _endDateTime;
public:
	DeleteBeforeCommand(boost::posix_time::ptime);
	UIFeedback DeleteCommand::execute(RunTimeStorage*);
	UIFeedback DeleteCommand::undo(void);
	virtual ~DeleteBeforeCommand(void);
};

class DeleteAllCommand: public DeleteCommand{
private:
	std::vector<Task> _tasksDeleted;
public:
	DeleteAllCommand(void);
	UIFeedback DeleteCommand::execute(RunTimeStorage*);
	UIFeedback DeleteCommand::undo(void);
	virtual ~DeleteAllCommand(void);
};
