#ifndef LOGIC_H_
#define LOGIC_H_

#include "..\APIContracts\CommandTokens.h"
#include "..\APIContracts\Task.h"
#include "..\APIContracts\UIFeedback.h"
#include "../ParserStub/Parser.h"
#include "StorageHandler.h"
#include "CommandCreator.h"
using namespace API;

const std::string MESSAGE_INVALID_COMMAND = "Invalid Command. No change is made.";

class Logic {
private:
	StorageHandler* _storageHandler;
	CommandCreator _commandCreator;
	Parser _parser;
	std::vector<Task> currentDisplay;
	std::string _fileName;

public:
	Logic(std::string fileName);

	UIFeedback executeCommand(std::string userString);
};

#endif