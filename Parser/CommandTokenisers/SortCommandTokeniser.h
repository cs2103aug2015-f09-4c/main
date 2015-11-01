//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class SortCommandTokeniser : public CommandTokeniser {
public:
	SortCommandTokeniser(void);
	virtual ~SortCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isSortName(std::string userInput);
	bool isSortStart(std::string userInput);
	bool isSortEnd(std::string userInput);

	void tokeniseSortName(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSortStart(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSortEnd(std::string userInput, CommandTokens* outputCommandTokens);

	std::string getSortOrder(std::string userInput);
};
