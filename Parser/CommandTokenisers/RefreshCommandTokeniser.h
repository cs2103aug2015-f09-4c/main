//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class RefreshCommandTokeniser : public CommandTokeniser {
public:
	RefreshCommandTokeniser(void);
	virtual ~RefreshCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isRefreshBasic(std::string userInput);
	void tokeniseRefreshBasic(std::string userInput, CommandTokens* outputCommandTokens);
};
