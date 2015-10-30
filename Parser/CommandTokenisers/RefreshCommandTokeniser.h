#pragma once
#include "..\CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Refresh PrimaryCommandType
// second, tokenises the entered command into the various arguments

class RefreshCommandTokeniser : public CommandTokeniser {
public:
	RefreshCommandTokeniser(void);
	virtual ~RefreshCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isRefreshCommand(std::string userInput);
	virtual bool isValidCommand(std::string userInput) override;

private:
	// identifiers to determine the exact type of REFRESH command called
	static bool isRefreshSimpliciterCommand(std::string userInput);

	// tokenisers for the various types of REFRESH commands
	void tokeniseRefreshSimpliciterCommand(std::string userInput);
};
