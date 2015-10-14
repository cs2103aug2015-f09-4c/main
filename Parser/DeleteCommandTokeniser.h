#pragma once
#include <regex>
#include "CommandTokens.h"
#include "CommandTokeniser.h"

class DeleteCommandTokeniser : public CommandTokeniser {
public:
	DeleteCommandTokeniser(void);
	virtual ~DeleteCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;

private:
	// identifiers to determine the exact type of DELETE command called
	bool isDeleteAll(std::string userInput);
	bool isDeleteFromTo(std::string userInput);
	bool isDeleteFrom(std::string userInput);
	bool isDeleteBy(std::string userInput);
	bool isDeleteIndex(std::string userInput);

	// tokenisers for the various types of DELETE commands
	void tokeniseDeleteAllCommand(void);
	void tokeniseDeleteFromToCommand(std::string userInput);
	void tokeniseDeleteFromCommand(std::string userInput);
	void tokeniseDeleteIndex(std::string userInput);
	void tokeniseDeleteByCommand(std::string userInput);
};
