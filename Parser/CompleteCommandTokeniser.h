#pragma once
#include "CommandTokeniser.h"

class CompleteCommandTokeniser : public CommandTokeniser {
public:
	CompleteCommandTokeniser(void);
	virtual ~CompleteCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	// tokenisers for the various types of COMPLETE commands
	void tokeniseCompleteCommand(std::string userInput);
};
