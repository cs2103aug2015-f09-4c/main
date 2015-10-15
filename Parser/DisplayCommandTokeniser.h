#pragma once
#include "CommandTokeniser.h"

class DisplayCommandTokeniser : public CommandTokeniser {
public:
	DisplayCommandTokeniser(void);
	virtual ~DisplayCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	// identifiers to determine the exact type of DISPLAY command called
	bool isDisplayAll(std::string userInput);
	bool isDisplayFromTo(std::string userInput);
	bool isDisplayFrom(std::string userInput);
	bool isDisplayBy(std::string userInput);
	bool isDisplayFloating(std::string userInput);

	// tokenisers for the various types of DISPLAY commands
	void tokeniseDisplayAllCommand(void);
	void tokeniseDisplayFromToCommand(std::string userInput);
	void tokeniseDisplayFromCommand(std::string userInput);
	void tokeniseDisplayByCommand(std::string userInput);
	void tokeniseDisplayFloatingCommand(std::string userInput);
};
