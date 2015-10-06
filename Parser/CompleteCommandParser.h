#pragma once
#include <regex>
#include "CommandTokens.h"

class CompleteCommandParser {
public:
	CompleteCommandParser(void);
	CommandTokens parse(std::string userInput);

private:
	CommandTokens _commandTokens;

	// tokenisers for the various types of COMPLETE commands
	void tokeniseCompleteCommand(std::string userInput);
};