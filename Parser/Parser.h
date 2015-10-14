#pragma once
#include <regex>
#include "CommandTokens.h"
#include "CommandTokeniser.h"
#include "AddCommandTokeniser.h"
#include "CompleteCommandTokeniser.h"
#include "DeleteCommandTokeniser.h"
#include "DisplayCommandTokeniser.h"
#include "EditCommandTokeniser.h"

// tokenises user input for Logic to do the necessary processing
class Parser {
public:
	Parser(void);
	CommandTokens parse(std::string userInput);

private:
	CommandTokens _commandTokens;
	AddCommandTokeniser _addCommandTokeniser;
	CompleteCommandTokeniser _completeCommandTokeniser;
	DeleteCommandTokeniser _deleteCommandTokeniser;
	DisplayCommandTokeniser _displayCommandTokeniser;
	EditCommandTokeniser _editCommandTokeniser;

	// extracts the primary command word
	PrimaryCommandType parsePrimaryCommand(std::string userInput);

	CommandTokeniser getCommandTokeniser(PrimaryCommandType primaryCommand);

	// examines the extracted primary command word extracted by
	// parsePrimaryCommand()
	bool isAddCommand(std::string& userInput);
	bool isCompleteCommand(std::string& userInput);
	bool isDeleteCommand(std::string& userInput);
	bool isEditCommand(std::string& userInput);
	bool isDisplayCommand(std::string& userInput);
	bool isUndoCommand(std::string& userInput);
};
