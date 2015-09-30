#pragma once

#include <regex>
#include "../APIContracts/CommandTokens.h"

// TODO: for testing purposes only
#define private public

// used to parse user input into CommandTokens for Logic to execute appropriate
// commands;
class Parser
{
public:
	CommandTokens parse(std::string userInput);
	bool isAddCommand(std::string& userInput);
	bool isDeleteCommand(std::string& userInput);
	bool isEditCommand(std::string& userInput);
	bool isDisplayCommand(std::string& userInput);
	private:
	CommandTokens _commandTokens;

	// constructor made private to prevent instantiation
	Parser(void);

	PrimaryCommandType extractPrimaryCommand(std::string userInput);

	void extractAddCommand(std::string userInput);
	void extractDeleteCommand(std::string userInput);
	void extractEditCommand(std::string userInput);
	void extractDisplayCommand(std::string userInput);

	bool isActivityTask(std::string userInput);
	bool isTodoTask(std::string userInput);

	bool isDeleteAll(std::string userInput);
	bool isDeleteFromTo(std::string userInput);
	bool isDeleteBy(std::string userInput);
	bool isDeleteFloating(std::string userInput);
	bool isDeleteIndex(std::string userInput);

	void extractActivityTask(std::string userInput);
	void extractTodoTask(std::string userInput);
	void extractFloatingTask(std::string userInput);

	boost::posix_time::ptime parseDate(std::string dateString);
};