#pragma once
#include "CommandTokeniser.h"

class AddCommandTokeniser : public CommandTokeniser {
public:
	AddCommandTokeniser(void);
	virtual ~AddCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

	static bool isAddCommand(std::string userInput);

private:
	// identifiers to determine the exact type of ADD command called
	static bool isAddActivityCommand(std::string userInput);
	static bool isAddTodoCommand(std::string userInput);
	static bool isAddFloatingCommand(std::string userInput);

	// tokenisers for the various types of ADD commands
	void tokeniseAddActivityCommand(std::string userInput);
	void tokeniseAddTodoCommand(std::string userInput);
	void tokeniseAddFloatingCommand(std::string userInput);
	void tokeniseTags(std::string userInput);

	std::string trimTags(std::string userInput);
	bool hasTags(std::string userInput);
};
