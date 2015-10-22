#pragma once
#include "CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Untag PrimaryCommandType
// second, tokenises the entered command into the various arguments
class UntagCommandTokeniser : public CommandTokeniser {
public:
	UntagCommandTokeniser(void);
	virtual ~UntagCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isUntagCommand(std::string userInput);

private:
	// identifiers to determine the exact type of UNTAG command called
	static bool isUntagIndexCommand(std::string userInput);

	// tokenisers for the various types of UNTAG commands
	void tokeniseUntagIndexCommand(std::string userInput);

	void tokeniseTags(std::string userInput);
};
