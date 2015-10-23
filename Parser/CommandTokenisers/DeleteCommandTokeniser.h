#pragma once
#include "..\CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Delete PrimaryCommandType
// second, tokenises the entered command into the various arguments
class DeleteCommandTokeniser : public CommandTokeniser {
public:
	DeleteCommandTokeniser(void);
	virtual ~DeleteCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isDeleteCommand(std::string userInput);

private:
	// identifiers to determine the exact type of DELETE command called
	static bool isDeleteAll(std::string userInput);
	static bool isDeleteFromTo(std::string userInput);
	static bool isDeleteFrom(std::string userInput);
	static bool isDeleteBy(std::string userInput);
	static bool isDeleteIndex(std::string userInput);

	// tokenisers for the various types of DELETE commands
	void tokeniseDeleteAllCommand(void);
	void tokeniseDeleteFromToCommand(std::string userInput);
	void tokeniseDeleteFromCommand(std::string userInput);
	void tokeniseDeleteIndex(std::string userInput);
	void tokeniseDeleteByCommand(std::string userInput);
};
