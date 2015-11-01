//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class UndoCommandTokeniser : public CommandTokeniser {
public:
	UndoCommandTokeniser(void);
	virtual ~UndoCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isUndoOnce(std::string userInput);
	void tokeniseUndoOnce(CommandTokens* outputCommandTokens);
};
