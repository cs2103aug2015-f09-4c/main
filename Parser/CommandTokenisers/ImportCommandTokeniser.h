#pragma once
#include "..\CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Import PrimaryCommandType
// second, tokenises the entered command into the various arguments
class ImportCommandTokeniser : public CommandTokeniser {
public:
	ImportCommandTokeniser(void);
	virtual ~ImportCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isImportCommand(std::string userInput);

private:
	// identifiers to determine the exact type of IMPORT command called
	static bool isImportLocalCommand(std::string userInput);

	// tokenisers for the various types of IMPORT commands
	void tokeniseImportLocalCommand(std::string userInput);
};
