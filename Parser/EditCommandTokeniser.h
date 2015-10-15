#pragma once
#include "CommandTokeniser.h"

class EditCommandTokeniser : public CommandTokeniser {
public:
	EditCommandTokeniser(void);
	virtual ~EditCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	// identifiers to determine the exact type of EDIT command called
	bool isEditName(std::string userInput);
	bool isEditStartDate(std::string userInput);
	bool isEditEndDate(std::string userInput);

	// tokenisers for the various types of EDIT commands
	void tokeniseEditNameCommand(std::string userInput);
	void tokeniseEditStartDateCommand(std::string userInput);
	void tokeniseEditEndDateCommand(std::string userInput);
};
