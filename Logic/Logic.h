#pragma once

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

public:
	Logic();

	UIFeedback executeCommand(std::string userString);

	virtual ~Logic();
};