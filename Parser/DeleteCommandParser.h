#pragma once
#include <regex>
#include "DateParser.h"
#include "CommandTokens.h"

class DeleteCommandParser {
public:
	DeleteCommandParser(void);
	CommandTokens parse(std::string userInput);

private:
	CommandTokens _commandTokens;
	DateParser _dateParser;
	
	// identifiers to determine the exact type of DELETE command called
	bool isDeleteAll(std::string userInput);
	bool isDeleteFromTo(std::string userInput);
	bool isDeleteFrom(std::string userInput);
	bool isDeleteBy(std::string userInput);
	bool isDeleteIndex(std::string userInput);

	// tokenisers for the various types of DELETE commands
	void tokeniseDeleteAllCommand(void);
	void tokeniseDeleteFromToCommand(std::string userInput);
	void tokeniseDeleteFromCommand(std::string userInput);
	void tokeniseDeleteIndex(std::string userInput);
	void tokeniseDeleteByCommand(std::string userInput);

	// adapter method to DateParser class
	boost::posix_time::ptime parseDate(std::string dateString);	
};

