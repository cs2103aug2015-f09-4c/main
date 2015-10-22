#pragma once
#include "CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Edit PrimaryCommandType
// second, tokenises the entered command into the various arguments
class EditCommandTokeniser : public CommandTokeniser {
public:
	EditCommandTokeniser(void);
	virtual ~EditCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isEditCommand(std::string userInput);

private:
	// identifiers to determine the exact type of EDIT command called
	static bool isEditName(std::string userInput);
	static bool isEditStartDate(std::string userInput);
	static bool isEditEndDate(std::string userInput);

	// tokenisers for the various types of EDIT commands
	void tokeniseEditNameCommand(std::string userInput);
	void tokeniseEditStartDateCommand(std::string userInput);
	void tokeniseEditEndDateCommand(std::string userInput);
};
