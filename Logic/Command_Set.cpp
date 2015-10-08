#include "Command_Set.h"

SetCompleteCommand::SetCompleteCommand(size_t index) : Command(PrimaryCommandType::Complete) {
	_type2 = SecondaryCommandType::Index;
	_index = index;
}

UIFeedback SetCompleteCommand::execute(StorageHandler* storageHandler) {
	Task& taskToSet = storageHandler->find(_index);
	std::string feedbackMessage;
	char buffer[255];
	
	if (!taskToSet.isValid()) {
		sprintf_s(buffer, MESSAGE_SET_COMPLETE_FAIL.c_str(), _index);
	} else if (taskToSet.isComplete()) {
		sprintf_s(buffer, MESSAGE_SET_COMPLETE_NO_CHANGE.c_str(), _index);
	} else {
		taskToSet.setComplete();
		_statusExecuted = true;
		sprintf_s(buffer, MESSAGE_SET_COMPLETE_SUCCESS.c_str(), _index);
	}

	feedbackMessage = std::string(buffer);
	UIFeedback feedback(storageHandler->getTasksToDisplay(), feedbackMessage);
	return feedback;
}

UIFeedback SetCompleteCommand::undo() {
	//TODO
	return UIFeedback();
}

bool SetCompleteCommand::canUndo() {
	return true;
}
