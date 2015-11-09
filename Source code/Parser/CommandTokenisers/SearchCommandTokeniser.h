//@@author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class SearchCommandTokeniser : public CommandTokeniser {
public:
	SearchCommandTokeniser(void);
	virtual ~SearchCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isSearchFreeSlot(std::string userInput);
	bool isSearchName(std::string userInput);
	bool isSearchFromTo(std::string userInput);
	bool isSearchStartBefore(std::string userInput);
	bool isSearchStartAfter(std::string userInput);
	bool isSearchEndBefore(std::string userInput);
	bool isSearchEndAfter(std::string userInput);
	bool isSearchTags(std::string userInput);
	
	void tokeniseSearchFreeSlot(CommandTokens* outputCommandTokens);
	void tokeniseSearchName(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchFromTo(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchStartBefore(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchStartAfter(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchEndBefore(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchEndAfter(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchTags(std::string userInput, CommandTokens* outputCommandTokens);
};
