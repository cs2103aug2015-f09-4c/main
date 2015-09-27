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

private:
	CommandTokens _commandTokens;

	// constructor made private to prevent instantiation
	Parser(void);

	PrimaryCommandType extractPrimaryCommand(std::string userInput);

	void extractAddCommand(std::string userInput);

	bool hasStartAndEndDate(std::string userInput);
	bool hasEndDate(std::string userInput);

	void extractAddCommandWithStartAndEndDate(std::string userInput);
	void extractAddCommandWithEndDate(std::string userInput);
	void extractAddCommandFloating(std::string userInput);

	int parseDate(std::string dateString);
};