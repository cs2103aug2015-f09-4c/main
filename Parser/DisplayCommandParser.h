#pragma once
#include <regex>
#include "DateParser.h"
#include "CommandTokens.h"

class DisplayCommandParser {
public:
	DisplayCommandParser(void);
	CommandTokens parse(std::string userInput);

private:
	CommandTokens _commandTokens;
	DateParser _dateParser;

	// identifiers to determine the exact type of DISPLAY command called
	bool isDisplayAll(std::string userInput);
	bool isDisplayFromTo(std::string userInput);
	bool isDisplayFrom(std::string userInput);
	bool isDisplayBy(std::string userInput);
	bool isDisplayFloating(std::string userInput);

	// tokenisers for the various types of DISPLAY commands
	void tokeniseDisplayAllCommand(void);
	void tokeniseDisplayFromToCommand(std::string userInput);
	void tokeniseDisplayFromCommand(std::string userInput);
	void tokeniseDisplayByCommand(std::string userInput);
	void tokeniseDisplayFloatingCommand(std::string userInput);

	// adapter method to DateParser class
	boost::posix_time::ptime parseDate(std::string dateString);
};

