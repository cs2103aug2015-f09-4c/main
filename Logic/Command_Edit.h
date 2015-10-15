#pragma once
#include "Command.h"

//Feedback message for different edit operation result
const std::string MESSAGE_EDIT_NAME_SUCCESS = "Task \"%s\" have been changed to \"%s\".";
const std::string MESSAGE_EDIT_NAME_EMPTY = "Task text cannot be empty. Task text is not changed.";
const std::string MESSAGE_EDIT_START_SUCCESS = "Task \"%s\" 's start date and time have been changed to \"%s\".";
const std::string MESSAGE_EDIT_END_SUCCESS = "Task \"%s\" 's end date and time have been changed to \"%s\".";

const std::string MESSAGE_EDIT_UNDO = "Previous edit operation have been undoed successfully.";

class EditCommand: public Command {
protected:
	size_t _index;
	size_t _editIndex;
public:
	EditCommand(SecondaryCommandType, size_t);
	virtual UIFeedback Command::execute(RunTimeStorage*) = 0;
	virtual UIFeedback Command::undo(void) = 0;
	bool canUndo(void);
};

class EditNameCommand: public EditCommand {
private:
	std::string _newTaskText;
	std::string _oldTaskText; //for undo later
public:
	EditNameCommand(size_t index, std::string newTaskText);
	UIFeedback EditCommand::execute(RunTimeStorage*);
	UIFeedback EditCommand::undo();
};

class EditStartCommand: public EditCommand {
private:
	boost::posix_time::ptime _newStart;
	boost::posix_time::ptime _oldStart;
public:
	EditStartCommand(size_t index, boost::posix_time::ptime newStart);
	UIFeedback EditCommand::execute(RunTimeStorage*);
	UIFeedback EditCommand::undo();
};

class EditEndCommand: public EditCommand {
private:
	boost::posix_time::ptime _newEnd;
	boost::posix_time::ptime _oldEnd; //for undo
public:
	EditEndCommand(size_t index, boost::posix_time::ptime newEnd);
	UIFeedback EditCommand::execute(RunTimeStorage*);
	UIFeedback EditCommand::undo();
};