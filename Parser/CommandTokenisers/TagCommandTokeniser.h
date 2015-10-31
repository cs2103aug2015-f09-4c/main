//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class TagCommandTokeniser : public CommandTokeniser {
public:
	TagCommandTokeniser(void);
	virtual ~TagCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isTagIndex(std::string userInput);
	void tokeniseTagIndex(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseTags(std::string userInput, CommandTokens* outputCommandTokens);
};
