#ifndef LOGIC_H_
#define LOGIC_H_

#include "..\..\Swiftask.h"
#include "Parser.h"
#include "StorageHandler.h"
#include "CommandCreator.h"

const std::string MESSAGE_INVALID_COMMAND = "Invalid Command. No change is made.";

class Logic {
private:
	StorageHandler* _storageHandler;
	CommandCreator _commandCreator;
	Parser _parser;
	std::vector<Task> currentDisplay;
	std::string _fileName;

public:
	Logic(std::string fileName)  {
		_fileName = fileName;
		_storageHandler = new StorageHandler(fileName);
	}

	UIFeedback executeCommand(std::string userString) {
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
};

#endif