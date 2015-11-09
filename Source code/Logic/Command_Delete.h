//@@author A0112218W

#pragma once

#include "Command.h"

//Feedback message for different delete operation result
const std::string MESSAGE_DELETE_INDEX_SUCCESS = "Task at index %i have been deleted successfully.";
const std::string MESSAGE_DELETE_ALL_SUCCESS = "All tasks have been removed.";
const std::string MESSAGE_DELETE_BEFORE_SUCCESS = "All tasks end before %s have been removed.";
const std::string MESSAGE_DELETE_FROMTO_SUCCESS = "All tasks start after %s and end before %s have been removed.";
const std::string MESSAGE_DELETE_COMPLETE_SUCCESS = "All completed tasks have been removed.";
const std::string MESSAGE_DELETE_EMPTY = "No task suited the condition is found. No task is deleted.";

const std::string MESSAGE_DELETE_UNDO = "Previous delete operation is undoed.";

/**
 *	Virtual command sub class responsible for deleting task
 */
class DeleteCommand: public Command{
public:
	/**
	 *	Constructor
	 *	@param type2 Secondary command type to further specify delete command.
	 */
	DeleteCommand (CommandTokens::SecondaryCommandType type2);

	virtual UIFeedback Command::execute(RunTimeStorage*) = 0;
	virtual UIFeedback Command::undo() = 0;

	/**
	 *	Return true all the time.
	 */
	bool canUndo();
};

/**
 *	Delete command sub class responsible for deleting tasks based on index shown in display.
 */
class DeleteIndexCommand: public DeleteCommand{
private:
	/**
	 *	Index of the task to be deleted shown in display.
	 */
	size_t _index;

	/**
	 *	Task that has been deleted by the command.
	 *	Used for undo.
	 */
	Task _taskDeleted;

	/**
	 *	Original index of the task deleted in master vector.
	 *	Used for undo.
	 */
	size_t _entryIndex;
public:
	/**
	 *	Constructor
	 *	@param index Index of task to be deleted as shown in display.
	 */
	DeleteIndexCommand(size_t index);

	/**
	 *	Execution method of deleteIndexCommand.
	 *	Delete task based on its index shown in display.
	 */
	UIFeedback DeleteCommand::execute(RunTimeStorage*);

	/**
	 *	Undo method of deleteIndexCommand.
	 *	Recover the task deleted back to its original position.
	 */
	UIFeedback DeleteCommand::undo(void);

	/**
	 *	Destructor
	 */
	virtual ~DeleteIndexCommand();
#ifdef TESTMODE
	size_t getIndex() {
		return _index;
	}
#endif
};

/**
 *	Delete command sub class responsible for deleting all tasks that end before date time specified.
 */
class DeleteBeforeCommand: public DeleteCommand{
private:
	/**
	 *	All tasks that have been deleted during execution.
	 */
	std::vector<Task> _tasksDeleted;

	/**
	 *	Original indexs of all tasks deleted in master vector.
	 */
	std::vector<int> _indexTaskDeleted;
	
	/**
	 *	Reference date time for comparison during execution.
	 */
	ptime _endDateTime;
public:
	/**
	 *	Constructor
	 *	@param end Date time used as reference. All tasks that end before it will be deleted during execution.
	 */
	DeleteBeforeCommand(ptime end);

	/**
	 *	Execution method of DeleteEndBeforeCommand.
	 *	Delete all tasks that end before _endDateTime.
	 */
	UIFeedback DeleteCommand::execute(RunTimeStorage*);

	/**
	 *	Undo method of DeleteBeforeCommand.
	 *	Recover all tasks deleted back to its original index in master vector.
	 */
	UIFeedback DeleteCommand::undo(void);

	/**
	 *	Destructor
	 */
	virtual ~DeleteBeforeCommand(void);
#ifdef TESTMODE
	ptime getEndDateTime() {
		return _endDateTime;
	}
#endif
};

/**
 *	Delete command sub class responsible for deleting tasks from date time 1 to date time2.
 */
class DeleteFromToCommand: public DeleteCommand{
private:
	/**
	 *	All tasks that have been deleted during execution.
	 */
	std::vector<Task> _tasksDeleted;

	/**
	 *	Original indexs of all tasks deleted in master vector.
	 */
	std::vector<int> _indexTaskDeleted;

	/**
	 *	Reference date time for comparison during execution.
	 */
	ptime _startDateTime;

	/**
	 *	Reference date time for comparison during execution.
	 */
	ptime _endDateTime;
public:
	/**
	 *	Constructor
	 *	@param start Date time used as reference.
	 *	@param end Date time used as reference.
	 */
	DeleteFromToCommand(ptime start, ptime end);

	/**
	 *	Execution method of DeleteFromToCommand.
	 *	Delete all tasks that start after _startDateTime and end before _endDateTime.
	 */
	UIFeedback DeleteCommand::execute(RunTimeStorage*);

	/**
	 *	Undo method of DeleteFromToCommand.
	 *	Recover all tasks deleted back to its original index in master vector.
	 */
	UIFeedback DeleteCommand::undo(void);

	/**
	 *	Destructor
	 */
	virtual ~DeleteFromToCommand(void);
#ifdef TESTMODE
	ptime getEndDateTime() {
		return _endDateTime;
	}

	ptime getStartDateTime() {
		return _startDateTime;
	}
#endif
};

/**
 *	Delete command sub class responsible for deleting all tasks.
 */
class DeleteAllCommand : public DeleteCommand{
private:
	/**
	 *	All tasks that have been deleted during execution.
	 */
	std::vector<Task> _tasksDeleted;
public:
	/**
	 *	Constructor
	 */
	DeleteAllCommand(void);

	/**
	 *	Execution method of DeleteAllCommand.
	 *	Delete all tasks.
	 */
	UIFeedback DeleteCommand::execute(RunTimeStorage*);

	/**
	 *	Undo method of DeleteAllCommand.
	 *	Recover all tasks deleted back to its original index in master vector.
	 */
	UIFeedback DeleteCommand::undo(void);

	/**
	 *	Destructor
	 */
	virtual ~DeleteAllCommand(void);
};

/**
 *	Delete command sub class responsible for deleting all completed tasks.
 */
class DeleteCompleteCommand : public DeleteCommand {
private:
	/**
	 *	All tasks that have been deleted during execution.
	 */
	std::vector<Task> _tasksDeleted;

	/**
	 *	Original indexs of all tasks deleted in master vector.
	 */
	std::vector<int> _indexTaskDeleted;
public:
	/**
	 *	Constructor
	 */	
	DeleteCompleteCommand (void);

	/**
	 *	Execution method of DeleteCompleteCommand.
	 *	Delete all completed tasks.
	 */
	UIFeedback DeleteCommand::execute(RunTimeStorage*);

	/**
	 *	Undo method of DeleteCompleteCommand.
	 *	Recover all tasks deleted back to its original index in master vector.
	 */
	UIFeedback DeleteCommand::undo(void);

	/**
	 *	Destructor.
	 */
	virtual ~DeleteCompleteCommand(void);
};