#pragma once
#include "..\CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Add PrimaryCommandType
// second, tokenises the entered command into the various arguments
class AddCommandTokeniser : public CommandTokeniser {
public:
	AddCommandTokeniser(void);
	virtual ~AddCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	virtual bool isValidCommand(std::string userInput) override;

private:
	// identifiers to determine the exact type of ADD command called
	static bool isAddFromTo(std::string userInput);
	static bool isAddBy(std::string userInput);
	static bool isAddFloating(std::string userInput);

	// tokenisers for the various types of ADD commands
	void tokeniseAddActivityCommand(std::string userInput);
	void tokeniseAddTodoCommand(std::string userInput);
	void tokeniseAddFloatingCommand(std::string userInput);
	void tokeniseTags(std::string userInput);

	std::string trimTags(std::string userInput);
	bool hasTags(std::string userInput);
};
