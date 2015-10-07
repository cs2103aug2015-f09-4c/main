#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include "CommandHeader.h"
#include "StorageHandler.h"
#include <stack>

using namespace API;

class CommandExecutor {
private:
	std::stack<Command*> _commandExecutedAndUndoable;
	std::stack<Command*> _commandUndoed;
	StorageHandler* _storageHandler;

public:
	CommandExecutor(std::string fileName);

	UIFeedback execute(Command* command);

	virtual ~CommandExecutor();
};

#endif