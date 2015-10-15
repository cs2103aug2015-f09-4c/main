#pragma once
#include <regex>
#include "CommandTokens.h"
#include "CommandTokeniser.h"
#include "AddCommandTokeniser.h"
#include "CompleteCommandTokeniser.h"
#include "DeleteCommandTokeniser.h"
#include "DisplayCommandTokeniser.h"
#include "EditCommandTokeniser.h"
#include "UndoCommandTokeniser.h"

// tokenises user input for Logic to do the necessary processing
class Parser {
public:
	Parser(void);
	CommandTokens parse(std::string userInput);

private:
	CommandTokeniser* _commandTokeniser;
	CommandTokens _invalidCommandTokens;

	// extracts the primary command word
	PrimaryCommandType getPrimaryCommand(std::string userInput);
	PrimaryCommandType parsePrimaryCommand(std::string userInput);
	void initialiseCommandTokeniser(PrimaryCommandType primaryCommandType);

	// examines the extracted primary command word extracted by
	// parsePrimaryCommand()
	bool isAddCommand(std::string& userInput);
	bool isCompleteCommand(std::string& userInput);
	bool isDeleteCommand(std::string& userInput);
	bool isEditCommand(std::string& userInput);
	bool isDisplayCommand(std::string& userInput);
	bool isUndoCommand(std::string& userInput);
};
