#pragma once
#include "..\CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Complete PrimaryCommandType
// second, tokenises the entered command into the various arguments
class CompleteCommandTokeniser : public CommandTokeniser {
public:
	CompleteCommandTokeniser(void);
	virtual ~CompleteCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isCompleteCommand(std::string userInput);
	virtual bool isValidCommand(std::string userInput) override;

private:
	// identifiers to determine the exact type of COMPLETE command called,
	// currently only one type
	static bool isCompleteIndexCommand(std::string userInput);

	// tokenisers for the various types of COMPLETE commands
	void tokeniseCompleteIndexCommand(std::string userInput);
};
