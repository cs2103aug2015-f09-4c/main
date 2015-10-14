#pragma once

#include <stack>
#include "CommandHeader.h"
#include "RunTimeStorage.h"

using namespace API;

class CommandExecutor {
private:
	std::stack<Command*> _commandExecutedAndUndoable;
	std::stack<Command*> _commandUndoed;
	RunTimeStorage* _runTimeStorage;

public:
	CommandExecutor();

	UIFeedback execute(Command* command);

	virtual ~CommandExecutor();
};
