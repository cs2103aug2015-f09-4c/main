//@@author A0112218W

#include "CommandExecutor.h"

UNDO_EXCEPTION::UNDO_EXCEPTION(const char* errorMessage) : std::exception(errorMessage) {
}

UNDO_EXCEPTION::UNDO_EXCEPTION(std::string errorMessage) : std::exception(errorMessage.c_str()) {
}

CommandExecutor::CommandExecutor() {
	_runTimeStorage = new RunTimeStorage();
}

UIFeedback CommandExecutor::execute(Command* command) {
	UIFeedback feedback;
	try {
		feedback = command -> execute (_runTimeStorage);
	} catch (COMMAND_EXECUTION_EXCEPTION e) {
		throw e;
	} 

	if (command -> isExecuted() && command->canUndo()) {
		_commandExecutedAndUndoable.push(command);
	} else {
		delete command;
	}

	_runTimeStorage->saveToFile();
	return feedback;
}

UIFeedback CommandExecutor::undo() {
	UIFeedback feedback;
	if (_commandExecutedAndUndoable.empty()) {
		throw UNDO_EXCEPTION(MESSAGE_UNDO_EMPTY);
	} 

	Command* command = _commandExecutedAndUndoable.top();

	try {
		_commandExecutedAndUndoable.pop();
		assert(command->canUndo());
		feedback = command -> undo();
	} catch (std::exception e) {
		throw e;
	}

	delete command;

	_runTimeStorage->saveToFile();
	return feedback;
}

CommandExecutor::~CommandExecutor() {
	while (!_commandExecutedAndUndoable.empty()) {
		delete _commandExecutedAndUndoable.top();
		_commandExecutedAndUndoable.top() = NULL;
		_commandExecutedAndUndoable.pop();
	}
	delete _runTimeStorage;
	_runTimeStorage = NULL;
}