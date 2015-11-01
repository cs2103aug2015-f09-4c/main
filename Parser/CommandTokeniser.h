//@@ author A0097681N
#pragma once
#include <regex>
#include "CommandTokens.h"
#include "DateParser.h"

class CommandTokeniser {
public:
	CommandTokeniser(void);
	virtual ~CommandTokeniser(void);

	virtual CommandTokens tokeniseUserInput(std::string userInput) = 0;
	virtual bool canTokeniseUserInput(std::string userInput) = 0;

protected:
	DateParser _dateParser;
	boost::posix_time::ptime parseUserInputDate(std::string userInputDate);
};
