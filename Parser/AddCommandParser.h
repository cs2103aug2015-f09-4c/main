#pragma once
#include <regex>
#include "CommandTokens.h"
#include "CommandTokeniser.h"

class AddCommandParser : public CommandTokeniser {
public:
	AddCommandParser(void);
	virtual ~AddCommandParser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
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
};