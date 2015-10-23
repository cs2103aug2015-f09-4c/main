#pragma once
#include "..\CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Tag PrimaryCommandType
// second, tokenises the entered command into the various arguments
class TagCommandTokeniser : public CommandTokeniser {
public:
	TagCommandTokeniser(void);
	virtual ~TagCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isTagCommand(std::string userInput);

private:
	// identifiers to determine the exact type of TAG command called
	static bool isTagIndexCommand(std::string userInput);

	// tokenisers for the various types of TAG commands
	void tokeniseTagIndexCommand(std::string userInput);

	void tokeniseTags(std::string userInput);
};
