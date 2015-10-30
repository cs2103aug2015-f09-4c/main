#pragma once
#include "..\CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Search PrimaryCommandType
// second, tokenises the entered command into the various arguments
class SearchCommandTokeniser : public CommandTokeniser {
public:
	SearchCommandTokeniser(void);
	virtual ~SearchCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isSearchCommand(std::string userInput);
	virtual bool isValidCommand(std::string userInput) override;

private:
	// identifiers to determine the exact type of SEARCH command called
	static bool isSearchNameCommand(std::string userInput);
	static bool isSearchStartBeforeCommand(std::string userInput);
	static bool isSearchStartAfterCommand(std::string userInput);
	static bool isSearchEndBeforeCommand(std::string userInput);
	static bool isSearchEndAfterCommand(std::string userInput);
	static bool isSearchTagsCommand(std::string userInput);

	// tokenisers for the various types of SEARCH commands
	void tokeniseSearchNameCommand(std::string userInput);
	void tokeniseSearchStartBeforeCommand(std::string userInput);
	void tokeniseSearchStartAfterCommand(std::string userInput);
	void tokeniseSearchEndBeforeCommand(std::string userInput);
	void tokeniseSearchEndAfterCommand(std::string userInput);
	void tokeniseSearchTagsCommand(std::string userInput);

	void tokeniseTags(std::string userInput);
};
