#pragma once
#include <regex>
#include "CommandTokens.h"
#include "AddCommandTokeniser.h"
#include "CompleteCommandTokeniser.h"
#include "DeleteCommandTokeniser.h"
#include "DisplayCommandParser.h"
#include "EditCommandParser.h"

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
	DisplayCommandParser _displayCommandParser;
	EditCommandParser _editCommandParser;

	// extracts the primary command word
	PrimaryCommandType parsePrimaryCommand(std::string userInput);

	// examines the extracted primary command word extracted by
	// parsePrimaryCommand()
	bool isAddCommand(std::string& userInput);
	bool isCompleteCommand(std::string& userInput);
	bool isDeleteCommand(std::string& userInput);
	bool isEditCommand(std::string& userInput);
	bool isDisplayCommand(std::string& userInput);
	bool isUndoCommand(std::string& userInput);
};
