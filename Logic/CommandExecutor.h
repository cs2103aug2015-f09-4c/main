#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include "Command.h"
#include "StorageHandler.h"
#include <stack>

using namespace API;

class CommandExecutor {
private:
	std::stack<Command*> _commandExecuted;
	std::stack<Command*> _commandUndoed;
	StorageHandler* _storageHandler;

public:
	CommandExecutor() {
		_storageHandler = NULL;
	}

	CommandExecutor(std::string fileName) {
		_storageHandler = new StorageHandler(fileName);
	}

	UIFeedback execute(Command* command) {
		UIFeedback feedback = command -> execute (_storageHandler);
		if (command -> isExecutedSuccessfully()) {
			_commandExecuted.push(command);
		}
		return feedback;
	}

	~CommandExecutor() {
		delete _storageHandler;
		_storageHandler = NULL;
	}

}

#endif