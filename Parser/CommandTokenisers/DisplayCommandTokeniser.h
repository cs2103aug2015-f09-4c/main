//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class DisplayCommandTokeniser : public CommandTokeniser {
public:
	DisplayCommandTokeniser(void);
	virtual ~DisplayCommandTokeniser(void);

	virtual bool canTokeniseUserInput(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isDisplayAll(std::string userInput);
	bool isDisplayActivity(std::string userInput);
	bool isDisplayTodo(std::string userInput);
	bool isDisplayFloating(std::string userInput);

	void tokeniseDisplayAll(CommandTokens* outputCommandTokens);
	void tokeniseDisplayActivity(CommandTokens* outputCommandTokens);
	void tokeniseDisplayTodo(CommandTokens* outputCommandTokens);
	void tokeniseDisplayFloating(CommandTokens* outputCommandTokens);
};
