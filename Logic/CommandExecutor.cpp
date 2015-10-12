#include "CommandExecutor.h"

CommandExecutor::CommandExecutor() {
	_runTimeStorage = new RunTimeStorage();
}

UIFeedback CommandExecutor::execute(Command* command) {
	UIFeedback feedback = command -> execute (_runTimeStorage);
	if (command -> isExecutedSuccessfully() && command->canUndo()) {
		_commandExecutedAndUndoable.push(command);
	} else {
		delete command;
	}
	_runTimeStorage->saveToFile();
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
	delete _runTimeStorage;
	_runTimeStorage = NULL;
}