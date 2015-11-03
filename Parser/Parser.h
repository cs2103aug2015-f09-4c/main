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
	CommandTokens _invalidCommandTokens;

	void initialiseAllCommandTokenisers(void);
	void initialiseInvalidCommandTokens(void);
	CommandTokeniser* getCommandTokeniser(std::string userInput);
};
