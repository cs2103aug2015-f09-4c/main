//@@ author A0097681N
#pragma once
#include <regex>
#include "CommandTokens.h"
#include "CommandTokeniser.h"
#include "Logger\Logger.h"

// facade class to provide uniform way to assess the various concrete
// CommandTokeniser classes
class Parser {
public:
	Parser(void);
	CommandTokens parse(std::string userInput);

private:
	Logger* _logger;

	std::vector<CommandTokeniser*> _commandTokenisers;
	CommandTokeniser* _commandTokeniser;
	CommandTokens _invalidCommandTokens;

	CommandTokeniser* getCommandTokeniser(std::string userInput);
};
