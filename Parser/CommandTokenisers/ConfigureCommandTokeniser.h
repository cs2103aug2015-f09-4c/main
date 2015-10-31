//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Configure PrimaryCommandType
// second, tokenises the entered command into the various arguments

class ConfigureCommandTokeniser : public CommandTokeniser {
public:
	ConfigureCommandTokeniser(void);
	virtual ~ConfigureCommandTokeniser(void);	
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isConfigureCommand(std::string userInput);
	virtual bool isValidCommand(std::string userInput) override;

private:
	// identifiers to determine the exact type of ADD command called
	static bool isConfigureSaveLocation(std::string userInput);

	// tokenisers for the various types of ADD commands
	void tokeniseConfigureSaveLocation(std::string userInput);
};
