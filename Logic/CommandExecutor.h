#pragma once

#include <stack>
#include "CommandHeader.h"
#include "RunTimeStorage.h"

using namespace API;

const std::string MESSAGE_UNDO_EMPTY = "There is no task available to undo. No change is made.";

class UNDO_EXCEPTION : public std::exception {
public:
	explicit UNDO_EXCEPTION(const char* errorMessage);

	explicit UNDO_EXCEPTION(std::string errorMessage);
};

class CommandExecutor {
private:
	std::stack<Command*> _commandExecutedAndUndoable;
	std::stack<Command*> _commandUndoed;
	RunTimeStorage* _runTimeStorage;

public:
	CommandExecutor();

	UIFeedback execute(Command* command);
	UIFeedback undo();

	virtual ~CommandExecutor();
};
