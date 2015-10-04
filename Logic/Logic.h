#ifndef LOGIC_H_
#define LOGIC_H_

#include "Task.h"
#include "UIFeedback.h"
#include "CommandExecutor.h"
#include "CommandCreator.h"
#include "..\Parser\Parser.h"
using namespace API;

class Logic {
private:
	CommandExecutor* _commandExecutor;
	CommandCreator _commandCreator;
	Parser _parser;
	std::string _fileName;

public:
	Logic(std::string fileName);

	UIFeedback executeCommand(std::string userString);
};

#endif