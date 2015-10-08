#include "Command_Invalid.h"

InvalidCommand::InvalidCommand(void) : Command(PrimaryCommandType::Invalid) {
	_message = MESSAGE_INVALID_COMMAND;
}

InvalidCommand::InvalidCommand(std::string message) : Command(PrimaryCommandType::Invalid){
	_message = message;
}

UIFeedback InvalidCommand::execute(StorageHandler* storageHandler) {
	UIFeedback feedback(storageHandler->getTasksToDisplay(), _message);

	//to specify this is invalid command
	_statusExecuted = false;
	
	return feedback;
}

UIFeedback InvalidCommand::undo() {
	return UIFeedback();
}

bool InvalidCommand::canUndo() {
	return false;
}


