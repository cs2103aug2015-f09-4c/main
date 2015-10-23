#pragma once
#include "..\CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Display PrimaryCommandType
// second, tokenises the entered command into the various arguments
class DisplayCommandTokeniser : public CommandTokeniser {
public:
	DisplayCommandTokeniser(void);
	virtual ~DisplayCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isDisplayCommand(std::string userInput);

private:
	// identifiers to determine the exact type of DISPLAY command called
	static bool isDisplayAll(std::string userInput);
	static bool isDisplayFromTo(std::string userInput);
	static bool isDisplayFrom(std::string userInput);
	static bool isDisplayBy(std::string userInput);
	static bool isDisplayFloating(std::string userInput);

	// tokenisers for the various types of DISPLAY commands
	void tokeniseDisplayAllCommand(void);
	void tokeniseDisplayFromToCommand(std::string userInput);
	void tokeniseDisplayFromCommand(std::string userInput);
	void tokeniseDisplayByCommand(std::string userInput);
	void tokeniseDisplayFloatingCommand();
};
