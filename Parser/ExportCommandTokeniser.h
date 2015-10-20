#pragma once
#include "CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Export PrimaryCommandType
// second, tokenises the entered command into the various arguments
class ExportCommandTokeniser : public CommandTokeniser {
public:
	ExportCommandTokeniser(void);
	virtual ~ExportCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isExportCommand(std::string userInput);

private:
	// identifiers to determine the exact type of EXPORT command called,
	// currently only one type
	static bool isExportToLocalDiskCommand(std::string userInput);

	// tokenisers for the various types of EXPORT commands
	void tokeniseExportToLocalDiskCommand(std::string userInput);
};
