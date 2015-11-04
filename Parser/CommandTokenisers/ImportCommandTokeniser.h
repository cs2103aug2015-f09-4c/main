//@@author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class ImportCommandTokeniser : public CommandTokeniser {
public:
	ImportCommandTokeniser(void);
	virtual ~ImportCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isImportLocal(std::string userInput);
	void tokeniseImportLocal(std::string userInput, CommandTokens* outputCommandTokens);
};
