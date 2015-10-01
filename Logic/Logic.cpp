#include "Logic.h"

Logic::Logic(std::string fileName)  {
	_fileName = fileName;
	_storageHandler = new StorageHandler(fileName);
}

UIFeedback Logic::executeCommand(std::string userString) {
	_parser = new Parser;
	CommandTokens commandTokens= _parser->parse(userString);
	if (commandTokens.isValid()) {
		Command* command= _commandCreator.process(commandTokens);
		UIFeedback feedback = command->execute(_storageHandler);
		delete command;
		return feedback;
	} else {
		UIFeedback feedback(_storageHandler->getTasksToDisplay(), MESSAGE_INVALID_COMMAND);
		return feedback;
	}
}