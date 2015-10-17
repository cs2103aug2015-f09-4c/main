#include "CommandExecutor.h"

CommandExecutor::CommandExecutor() {
	_runTimeStorage = new RunTimeStorage();
}

UIFeedback CommandExecutor::undo() {
	UIFeedback feedback;
	try {
		if (_commandExecutedAndUndoable.empty()) {
			feedback = UIFeedback(_runTimeStorage->getTasksToDisplay(), MESSAGE_UNDO_EMPTY);
		} else {
			Command* command = _commandExecutedAndUndoable.top();
			_commandExecutedAndUndoable.pop();
			assert(command->canUndo());
			feedback = command -> undo();
			_commandUndoed.push(command);
		}
	} catch (std::string errorMessage) {
		feedback = UIFeedback(_runTimeStorage->getTasksToDisplay(), errorMessage);
	}
	return feedback;
}

UIFeedback CommandExecutor::execute(Command* command) {
	UIFeedback feedback;
	try {
		feedback = command -> execute (_runTimeStorage);
	} catch (std::string errorMessage) {
		feedback = UIFeedback(_runTimeStorage->getTasksToDisplay(), errorMessage);
	}

	if (command -> isExecuted() && command->canUndo()) {
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