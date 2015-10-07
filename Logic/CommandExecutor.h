#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

#include "CommandHeader.h"
#include "StorageHandler.h"
#include <stack>

using namespace API;

class CommandExecutor {
private:
	std::stack<Command*> _commandExecuted;
	std::stack<Command*> _commandUndoed;
	StorageHandler* _storageHandler;

public:
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
		while (!_commandExecuted.empty()) {
			delete _commandExecuted.top();
			_commandExecuted.top() = NULL;
			_commandExecuted.pop();
		}
		while (!_commandUndoed.empty()) {
			delete _commandUndoed.top();
			_commandUndoed.top() = NULL;
			_commandUndoed.pop();
		}
		delete _storageHandler;
		_storageHandler = NULL;
	}

};

#endif