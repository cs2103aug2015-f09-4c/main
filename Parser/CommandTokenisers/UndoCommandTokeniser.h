#pragma once
#include "..\CommandTokeniser.h"

// serves two related purposes:
// first, provides a static public method to check if an entered command is
// indeed of Undo PrimaryCommandType
// second, tokenises the entered command into the various arguments
class UndoCommandTokeniser : public CommandTokeniser {
public:
	UndoCommandTokeniser(void);
	virtual ~UndoCommandTokeniser(void);
	virtual CommandTokens tokeniseUserInput(std::string userInput) override;
	static bool isUndoCommand(std::string userInput);

private:
	// identifiers to determine the exact type of UNDO command called
	static bool isUndoOnceCommand(std::string userInput);

	// tokenisers for the various types of UNDO commands
	void tokeniseUndoOnceCommand();
};
