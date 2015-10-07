#include "CommandExecutor.h"

CommandExecutor::CommandExecutor(std::string fileName) {
	_storageHandler = new StorageHandler(fileName);
}

UIFeedback CommandExecutor::execute(Command* command) {
	UIFeedback feedback = command -> execute (_storageHandler);
	if (command -> isExecutedSuccessfully() && command->canUndo()) {
		_commandExecutedAndUndoable.push(command);
	} else {
		delete command;
	}
	return feedback;
}

CommandExecutor::~CommandExecutor() {
	while (!_commandExecutedAndUndoable.empty()) {
		delete _commandExecutedAndUndoable.top();
		_commandExecutedAndUndoable.top() = NULL;
		_commandExecutedAndUndoable.pop();
	}
	while (!_commandUndoed.empty()) {
		delete _commandUndoed.top();
		_commandUndoed.top() = NULL;
		_commandUndoed.pop();
	}
	delete _storageHandler;
	_storageHandler = NULL;
}