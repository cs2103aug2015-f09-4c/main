//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class UntagCommandTokeniser : public CommandTokeniser {
public:
	UntagCommandTokeniser(void);
	virtual ~UntagCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isUntagIndex(std::string userInput);
	void tokeniseUntagIndex(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseTags(std::string userInput, CommandTokens* outputCommandTokens);
};
