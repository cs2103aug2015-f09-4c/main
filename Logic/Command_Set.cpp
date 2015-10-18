#include "Command_Set.h"

SetCompleteCommand::SetCompleteCommand(size_t index) : Command(CommandTokens::PrimaryCommandType::Complete) {
	_type2 = CommandTokens::SecondaryCommandType::Index;
	_index = index;
}

UIFeedback SetCompleteCommand::execute(RunTimeStorage* runTimeStorage) {
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
		throw std::string(e.what());
	} catch (ALREADY_COMPLETE_EXCEPTION e) {
		throw std::string(e.what());
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
