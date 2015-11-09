//@@author A0112218W
#pragma once
#include "Command.h"

//Feedback message for different edit operation result
const std::string MESSAGE_EDIT_NAME_SUCCESS = "Task \"%s\" have been changed to \"%s\".";
const std::string MESSAGE_EDIT_NAME_EMPTY = "Task text cannot be empty. Task text is not changed.";
const std::string MESSAGE_EDIT_START_SUCCESS = "Task \"%s\" 's start date and time have been changed to \"%s\".";
const std::string MESSAGE_EDIT_END_SUCCESS = "Task \"%s\" 's end date and time have been changed to \"%s\".";
const std::string MESSAGE_EDIT_DUPLICATE = "Edit will cause task duplication, edit cannot be performed.";

const std::string MESSAGE_EDIT_UNDO = "Previous edit operation have been undoed successfully.";

/**
 *	Virtual Command sub class responsible for editing task attribute.
 */
class EditCommand: public Command {
protected:
	/**
	 *	Index of the task to be edited as shown in display(1-based)
	 */
	size_t _index;

	/**
	 *	Index of the task in master vector (0-based), used for undo
	 */
	size_t _editIndex;
public:
	/**
	 *	Constructor
	 *	@param type2 Secondary Command Type to further specify Edit Command
	 *	@param index Index of the task to be edited as shown in display (1-based)
	 */
	EditCommand(CommandTokens::SecondaryCommandType type2, size_t index);

	virtual UIFeedback Command::execute(RunTimeStorage*) = 0;
	virtual UIFeedback Command::undo(void) = 0;

	/**
	 *	Return true all the time
	 */
	bool canUndo(void);
};

/**
 *	EditCommand sub class responsible for editing task name
 */
class EditNameCommand: public EditCommand {
private:
	/**
	 *	New task name to change to
	 */
	std::string _newTaskText;

	/**
	 *	Original name of the edited task, used for undo
	 */
	std::string _oldTaskText;
public:
	/**
	 *	Constructor
	 *	@param index Index of the task to be edited as shown in display. (1-based)
	 *	@param newTaskText New task name to change to
	 */
	EditNameCommand(size_t index, std::string newTaskText);

	/**
	 *	Execution method of EditNameCommand.
	 *	Change name of the specified task based on index.
	 */
	UIFeedback EditCommand::execute(RunTimeStorage*);

	/**
	 *	Undo method of EditNameCommand.
	 *	Revert back name of edited task.
	 */
	UIFeedback EditCommand::undo();
};

/**
 *	EditCommand sub class responsible for editing start date time
 */
class EditStartCommand: public EditCommand {
private:
	/**
	 *	New start date time to change to
	 */
	ptime _newStart;

	/**
	 *	Original start date time of the edited task, used for undo
	 */
	ptime _oldStart;
public:
	/**
	 *	Constructor
	 *	@param index Index of the task to be edited as shown in display. (1-based)
	 *	@param newStart New start date time to change to
	 */
	EditStartCommand(size_t index, ptime newStart);

	/**
	 *	Execution method of EditStartCommand.
	 *	Change start date time of the specified task based on index.
	 */
	UIFeedback EditCommand::execute(RunTimeStorage*);

	/**
	 *	Undo method of EditStartCommand.
	 *	Revert back start date time of edited task.
	 */
	UIFeedback EditCommand::undo();
};

/**
 *	EditCommand sub class responsible for editing end date time
 */
class EditEndCommand: public EditCommand {
private:
	/**
	 *	New end date time to change to
	 */
	ptime _newEnd;

	/**
	 *	Original end date time of the edited task, used for undo
	 */
	ptime _oldEnd; 
public:
	/**
	 *	Constructor
	 *	@param index Index of the task to be edited as shown in display. (1-based)
	 *	@param newEnd New end date time to change to
	 */
	EditEndCommand(size_t index, ptime newEnd);

	/**
	 *	Execution method of EditEndCommand.
	 *	Change end date time of the specified task based on index.
	 */
	UIFeedback EditCommand::execute(RunTimeStorage*);

	/**
	 *	Undo method of EditEndCommand.
	 *	Revert back end date time of edited task.
	 */
	UIFeedback EditCommand::undo();
};