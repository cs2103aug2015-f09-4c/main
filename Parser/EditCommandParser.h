#pragma once
#include <regex>
#include "DateParser.h"
#include "CommandTokens.h"

class EditCommandParser {
public:
	EditCommandParser(void);
	CommandTokens parse(std::string userInput);

private:
	CommandTokens _commandTokens;
	DateParser _dateParser;

	// identifiers to determine the exact type of EDIT command called
	bool isEditName(std::string userInput);
	bool isEditStartDate(std::string userInput);
	bool isEditEndDate(std::string userInput);

	// tokenisers for the various types of EDIT commands
	void tokeniseEditNameCommand(std::string userInput);
	void tokeniseEditStartDateCommand(std::string userInput);
	void tokeniseEditEndDateCommand(std::string userInput);

	// adapter method to DateParser class
	boost::posix_time::ptime parseDate(std::string dateString);
};

