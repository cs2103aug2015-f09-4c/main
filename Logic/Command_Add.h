//@@author A0112218W
#pragma once
#include "Command.h"

//Feedback message for different add operation result
const std::string MESSAGE_ADD_SUCCESS = "\"%s\" have been added succesfully.\nStart Date Time: %s\nEnd Date Time: %s"; 
const std::string MESSAGE_ADD_EMPTY = "Task text cannot be empty. New task is not added.";

//Feedback message when add operation is undoed
const std::string MESSAGE_UNDO_ADD = "Previous add operation is undoed succesfully";

/**
 *	Command sub class that is responsible for adding task
 */
class AddCommand: public Command {
private:
	/**
	 *	Task to be added.
	 */
	Task _task;
public:
	/**
	 *	Constructor
	 *	@param type2 SecondaryCommandType which corresponding to the type of task added.
	 *	@param task Task to be added.
	 */
	AddCommand (CommandTokens::SecondaryCommandType type2, Task task);

	/**
	 *	Execution method of AddCommand.
	 *	_task will be added to RunTimeStorage* provided.
	 */
	UIFeedback execute(RunTimeStorage*);

	/**
	 *	Undo method of AddCommand.
	 *	Will remove the task added to RunTimeStorage.
	 *
	 */
	UIFeedback undo(void);

	/**
	 *	Return true all the time.
	 */
	bool canUndo();

	virtual ~AddCommand(void);

#ifdef TESTMODE

	Task getTask() {
		return _task;
	}

#endif
};