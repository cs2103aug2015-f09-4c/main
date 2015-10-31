//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class CompleteCommandTokeniser : public CommandTokeniser {
public:
	CompleteCommandTokeniser(void);
	virtual ~CompleteCommandTokeniser(void);

	virtual bool isValidCommand(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isCompleteIndex(std::string userInput);
	void tokeniseCompleteIndex(std::string userInput, CommandTokens* outputCommandTokens);
};
