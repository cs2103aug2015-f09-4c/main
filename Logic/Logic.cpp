#include "Logic.h"

Logic::Logic(std::string fileName)  {
	_fileName = fileName;
	_storageHandler = new StorageHandler(fileName);
}

UIFeedback Logic::executeCommand(std::string userString) {
	CommandTokens commandTokens= _parser.parse(userString);
	if (commandTokens.isValid()) {
		Command* command= _commandCreator.process(commandTokens);
		UIFeedback feedback = command->execute(_storageHandler);
		currentDisplay = feedback.getTasksForDisplay();
		return feedback;
	} else {
		UIFeedback feedback(currentDisplay, MESSAGE_INVALID_COMMAND);
		return feedback;
	}
}