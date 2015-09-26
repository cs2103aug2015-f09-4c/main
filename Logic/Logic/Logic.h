#ifndef LOGIC_H_
#define LOGIC_H_

#include "..\..\APIContracts\CommandTokens.h"
#include "..\..\APIContracts\Task.h"
#include "..\..\APIContracts\UIFeedback.h"
#include "Parser.h"
#include "StorageHandler.h"
#include "CommandCreator.h"

const string MESSAGE_INVALID_COMMAND = "Invalid Command. No change is made.";

class Logic {
private:
	StorageHandler _storageHandler(string filePath);
	CommandCreator _commandCreator;
	std::vector<Task> currentDisplay;
	std::string _fileName;

public:
	Logic(string fileName)  {
		_fileName = fileName;
	}

	UIFeedback executeCommand(userString) {
		CommandTokens commandTokens= Parser.parse(userString);
		if (commandTokens.isValid() {
			Command command= _commandCreator.process(commandTokens);
			UIFeedback feedback = _storageHandler.process(command);
			currentDisplay = feedback.getTaskForDisplay();
			return feedback;
		} else {
			UIFeedback feedback(currentDisplay, MESSAGE_INVALID_COMMAND);
			return feedback;
		}
	}
};

#endif