#include "Command_Set.h"

ALREADY_COMPLETE_EXCEPTION::ALREADY_COMPLETE_EXCEPTION(int index) : std::exception() {
	sprintf_s(_message, MESSAGE_SET_COMPLETE_NO_CHANGE.c_str(), index);
}

const char* ALREADY_COMPLETE_EXCEPTION::what(void) const throw() {
	return _message;
}


SetCompleteCommand::SetCompleteCommand(size_t index) : Command(CommandTokens::PrimaryCommandType::Complete) {
	_type2 = CommandTokens::SecondaryCommandType::Index;
	_index = index;
}

UIFeedback SetCompleteCommand::execute(RunTimeStorage* runTimeStorage) {
	assert (runTimeStorage != NULL);

	UIFeedback feedback;

	try {
		Task& taskToSet = runTimeStorage->find(_index);
		_setIndex = runTimeStorage->find(taskToSet);
		std::string feedbackMessage;
		char buffer[255];
		if (taskToSet.isComplete()) {
			throw ALREADY_COMPLETE_EXCEPTION(_index);
		}
		taskToSet.toggleComplete();
		_statusExecuted = true;
		_runTimeStorageExecuted = runTimeStorage;
		sprintf_s(buffer, MESSAGE_SET_COMPLETE_SUCCESS.c_str(), _index);

		feedbackMessage = std::string(buffer);
		feedback = UIFeedback(runTimeStorage->getTasksToDisplay(), feedbackMessage);
	} catch (INDEX_NOT_FOUND_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	} catch (ALREADY_COMPLETE_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	}
	return feedback;
}

UIFeedback SetCompleteCommand::undo() {
	assert(_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);

	Task& taskToSet = _runTimeStorageExecuted->getEntry(_setIndex);

	assert(taskToSet.isComplete());
	taskToSet.toggleComplete();

	return UIFeedback(_runTimeStorageExecuted->getTasksToDisplay(), MESSAGE_SET_UNDO);
}

bool SetCompleteCommand::canUndo() {
	return true;
}
