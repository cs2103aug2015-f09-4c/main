//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class ConfigureCommandTokeniser : public CommandTokeniser {
public:
	ConfigureCommandTokeniser(void);
	virtual ~ConfigureCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isConfigureSaveLocation(std::string userInput);
	void tokeniseConfigureSaveLocation(std::string userInput, CommandTokens* outputCommandTokens);
};
