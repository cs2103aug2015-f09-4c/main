#pragma once
#include "CommandTokeniser.h"

class UndoCommandTokeniser : public CommandTokeniser {
public:
	UndoCommandTokeniser(void);
	virtual ~UndoCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
};
