#include "Parser.h"

Parser::Parser(void) {
	_commandTokens.setPrimaryCommand(PrimaryCommandType::Invalid);
}

CommandTokens Parser::parse(std::string userInput) {
	PrimaryCommandType primaryCommand = parsePrimaryCommand(userInput);
	_commandTokens.setPrimaryCommand(primaryCommand);

	switch (primaryCommand) {
		case Add:
			return _addCommandTokeniser.tokeniseUserInput(userInput);
		case Complete:
			return _completeCommandTokeniser.tokeniseUserInput(userInput);
		case Delete:
			return _deleteCommandTokeniser.tokeniseUserInput(userInput);
		case Display:
			return _displayCommandTokeniser.tokeniseUserInput(userInput);
		case Edit:
			return _editCommandTokeniser.tokeniseUserInput(userInput);
		case Undo:
			return _commandTokens;
		case Invalid:
			return _commandTokens;
		default:
			return _commandTokens;
	}
}

PrimaryCommandType Parser::parsePrimaryCommand(std::string userInput) {
	PrimaryCommandType commandType = Invalid;

	if (isAddCommand(userInput)) {
		commandType = Add;
	} else if (isDeleteCommand(userInput)) {
		commandType = Delete;
	} else if (isEditCommand(userInput)) {
		commandType = Edit;
	} else if (isDisplayCommand(userInput)) {
		commandType = Display;
	} else if (isCompleteCommand(userInput)) {
		commandType = Complete;
	} else if (isUndoCommand(userInput)) {
		commandType = Undo;
	}

	return commandType;
}

bool Parser::isAddCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("add .+",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool Parser::isCompleteCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("complete .+",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool Parser::isDeleteCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("delete .+",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool Parser::isDisplayCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("display .+",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool Parser::isEditCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("edit .+",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool Parser::isUndoCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("undo.*",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}
