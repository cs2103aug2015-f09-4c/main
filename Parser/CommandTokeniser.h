//@@ author A0097681N
#pragma once
#include <regex>
#include "CommandTokens.h"
#include "DateParser.h"

// abstract class used to create concrete class for processing each kind of
// command;
// usage: implement canTokeniseUserInput() to return true for user input that
// the concrete class is supposed to process; implement tokeniserUserInput()
// for actual tokenising of the user input
class CommandTokeniser {
public:
	CommandTokeniser(void);
	virtual ~CommandTokeniser(void);

	virtual CommandTokens tokeniseUserInput(std::string userInput) = 0;
	virtual bool canTokeniseUserInput(std::string userInput) = 0;

protected:
	// utility methods for common user input processing tasks
	DateParser _dateParser;
	boost::posix_time::ptime parseUserInputDate(std::string userInputDate);

	bool isRegexMatch(std::string userInput, std::string regexString);
};
