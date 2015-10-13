#pragma once

#include <string>
#include "CommandTokens.h"
#include "DateParser.h"

class CommandTokeniser {
public:
	CommandTokeniser(void);
	~CommandTokeniser(void);

	virtual CommandTokens tokeniseUserInput(std::string userInput) = 0;

private:
	CommandTokens _commandTokens;
	DateParser _dateParser;

	boost::posix_time::ptime parseUserInputDate(std::string userInputDate);
};