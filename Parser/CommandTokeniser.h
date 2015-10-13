#pragma once

#include <string>
#include "CommandTokens.h"
#include "DateParser.h"

class CommandTokeniser {
public:
	CommandTokeniser(void);
	virtual ~CommandTokeniser(void);

	virtual CommandTokens tokeniseUserInput(std::string userInput) = 0;

protected:
	CommandTokens _commandTokens;
	DateParser _dateParser;

	boost::posix_time::ptime parseUserInputDate(std::string userInputDate);
};