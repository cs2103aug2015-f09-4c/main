#pragma once

#include <regex>
#include "CommandTokens.h"

// TODO: for testing purposes only
#define private public

// used to parse user input into CommandTokens for Logic to execute appropriate
// commands;
class Parser {
public:
	Parser(void);
	CommandTokens parse(std::string userInput);

private:
	CommandTokens _commandTokens;

	// extracts the primary command word
	PrimaryCommandType parsePrimaryCommand(std::string userInput);

	// examines the extracted primary command word extracted by 
	// parsePrimaryCommand()
	bool isAddCommand(std::string& userInput);
	bool isDeleteCommand(std::string& userInput);
	bool isEditCommand(std::string& userInput);
	bool isDisplayCommand(std::string& userInput);
	
	void tokeniseAddCommand(std::string userInput);
	void tokeniseDeleteCommand(std::string userInput);
	void tokeniseEditCommand(std::string userInput);
	void tokeniseDisplayCommand(std::string userInput);

	// identifiers to determine the exact type of ADD command called
	bool isAddActivityTask(std::string userInput);
	bool isAddTodoTask(std::string userInput);
	// tokenisers for the various types of ADD commands
	void tokeniseActivityTask(std::string userInput);
	void tokeniseTodoTask(std::string userInput);
	void tokeniseFloatingTask(std::string userInput);	
	
	// identifiers to determine the exact type of DELETE command called
	bool isDeleteAll(std::string userInput);
	bool isDeleteFromTo(std::string userInput);
	bool isDeleteBy(std::string userInput);
	bool isDeleteFloating(std::string userInput);
	bool isDeleteIndex(std::string userInput);
	// tokenisers for the various types of DELETE commands
	void tokeniseDeleteAllCommand(void);
	void tokeniseDeleteFromToCommand(std::string userInput);
	void tokeniseDeleteIndex(std::string userInput);
	void tokeniseDeleteByCommand(std::string userInput);
	void tokeniseDeleteFloatingCommand(std::string userInput);
	
	// identifiers to determine the exact type of DISPLAY command called
	bool isDisplayAll(std::string userInput);
	bool isDisplayFromTo(std::string userInput);
	bool isDisplayBy(std::string userInput);
	bool isDisplayFloating(std::string userInput);
	// tokenisers for the various types of DISPLAY commands
	void tokeniseDisplayAllCommand(void);
	void tokeniseDisplayFromToCommand(std::string userInput);
	void tokeniseDisplayByCommand(std::string userInput);
	void tokeniseDisplayFloatingCommand(std::string userInput);

	// identifiers to determine the exact type of EDIT command called
	bool isEditName(std::string userInput);
	bool isEditStartDate(std::string userInput);
	bool isEditEndDate(std::string userInput);
	// tokenisers for the various types of EDIT commands
	void tokeniseEditNameCommand(std::string userInput);
	void tokeniseEditStartDateCommand(std::string userInput);
	void tokeniseEditEndDateCommand(std::string userInput);

	// parses user input data/time string into ptime format
	boost::posix_time::ptime parseDate(std::string dateString);
};