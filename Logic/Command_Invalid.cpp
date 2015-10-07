#include "Command_Invalid.h"

InvalidCommand::InvalidCommand(std::string message) : Command(PrimaryCommandType::Invalid){
	_message = message;
}

UIFeedback InvalidCommand::execute(StorageHandler* storageHandler) {
	UIFeedback feedback(storageHandler->getTasksToDisplay(), _message);

	//to specify this is invalid command
	_statusExecuted = false;
	
	return feedback;
}
