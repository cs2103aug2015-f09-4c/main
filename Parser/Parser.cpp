#include "Parser.h"

Parser::Parser(void) {
	_commandTokens.setPrimaryCommand(PrimaryCommandType::Invalid);
}

CommandTokens Parser::parse(std::string userInput) {
	PrimaryCommandType primaryCommand = parsePrimaryCommand(userInput);

	switch (primaryCommand) {
	case Add:
		return _addCommandParser.parse(userInput);
	case Complete:
		return _completeCommandParser.parse(userInput);
	case Delete:
		return _deleteCommandParser.parse(userInput);
	case Display:
		return _displayCommandParser.parse(userInput);
	case Edit:
		return _editCommandParser.parse(userInput);
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
	}
	return commandType;
}

bool Parser::isAddCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("add .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool Parser::isCompleteCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("complete .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool Parser::isDeleteCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("delete .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

bool Parser::isDisplayCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("display .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

bool Parser::isEditCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("edit .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}