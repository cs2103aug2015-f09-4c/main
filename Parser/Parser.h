#pragma once
#include <regex>
#include <string>
#include "CommandTokens.h"
#include "AddCommandParser.h"
#include "CompleteCommandParser.h"
#include "DisplayCommandParser.h"
#include "DeleteCommandParser.h"
#include "EditCommandParser.h"

// TODO: for testing purposes only
//#define private public

// tokenises user input for Logic to do the necessary processing
class Parser {
public:
	Parser(void);
	CommandTokens parse(std::string userInput);

private:
	CommandTokens _commandTokens;
	AddCommandParser _addCommandParser;
	CompleteCommandParser _completeCommandParser;
	DisplayCommandParser _displayCommandParser;
	DeleteCommandParser _deleteCommandParser;
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