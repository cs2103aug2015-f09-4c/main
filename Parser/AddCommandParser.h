#pragma once
#include <regex>
#include "DateParser.h"
#include "CommandTokens.h"

class AddCommandParser {
public:
	AddCommandParser(void);
	CommandTokens parse(std::string userInput);

private:
	CommandTokens _commandTokens;
	DateParser _dateParser;

	// identifiers to determine the exact type of ADD command called
	bool isAddActivityCommand(std::string userInput);
	bool isAddTodoCommand(std::string userInput);

	// tokenisers for the various types of ADD commands
	void tokeniseAddActivityCommand(std::string userInput);
	void tokeniseAddTodoCommand(std::string userInput);
	void tokeniseAddFloatingCommand(std::string userInput);
	void tokeniseTags(std::string userInput);

	std::string trimTags(std::string userInput);
	bool hasTags(std::string userInput);

	// adapter method to DateParser class
	boost::posix_time::ptime parseDate(std::string dateString);
};