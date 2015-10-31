//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class SearchCommandTokeniser : public CommandTokeniser {
public:
	SearchCommandTokeniser(void);
	virtual ~SearchCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	static bool isSearchName(std::string userInput);
	static bool isSearchStartBefore(std::string userInput);
	static bool isSearchStartAfter(std::string userInput);
	static bool isSearchEndBefore(std::string userInput);
	static bool isSearchEndAfter(std::string userInput);
	static bool isSearchTags(std::string userInput);

	void tokeniseSearchName(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchStartBefore(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchStartAfter(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchEndBefore(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchEndAfter(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseSearchTags(std::string userInput, CommandTokens* outputCommandTokens);
};
