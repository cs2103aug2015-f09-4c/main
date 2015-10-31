//@@ author A0097681N
#pragma once
#include "..\CommandTokeniser.h"

class DisplayCommandTokeniser : public CommandTokeniser {
public:
	DisplayCommandTokeniser(void);
	virtual ~DisplayCommandTokeniser(void);

	virtual bool isValidCommand(std::string userInput) override;
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	bool isDisplayAll(std::string userInput);
	bool isDisplayFloating(std::string userInput);
	bool isDisplayFromTo(std::string userInput);
	bool isDisplayFrom(std::string userInput);
	bool isDisplayBy(std::string userInput);

	void tokeniseDisplayAll(CommandTokens* outputCommandTokens);
	void tokeniseDisplayFloating(CommandTokens* outputCommandTokens);
	void tokeniseDisplayFromTo(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseDisplayFrom(std::string userInput, CommandTokens* outputCommandTokens);
	void tokeniseDisplayBy(std::string userInput, CommandTokens* outputCommandTokens);
};
