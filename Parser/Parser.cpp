#include <assert.h>
#include "Parser.h"
#include "AddCommandTokeniser.h"
#include "CompleteCommandTokeniser.h"
#include "DeleteCommandTokeniser.h"
#include "DisplayCommandTokeniser.h"
#include "EditCommandTokeniser.h"
#include "UndoCommandTokeniser.h"

Parser::Parser(void) {
	_logger = Logger::getInstance();

	_commandTokeniser = nullptr;
	_invalidCommandTokens.setPrimaryCommand(PrimaryCommandType::Invalid);
	_invalidCommandTokens.setSecondaryCommand(SecondaryCommandType::None);
}

CommandTokens Parser::parse(std::string userInput) {
	_logger->logINFO("Parsing user input: " + userInput);

	// inclusion guard
	PrimaryCommandType primaryCommandType = getPrimaryCommand(userInput);
	if (primaryCommandType == PrimaryCommandType::Invalid) {
		return _invalidCommandTokens;
	}

	initialiseCommandTokeniser(primaryCommandType);

	return _commandTokeniser->tokeniseUserInput(userInput);
}

PrimaryCommandType Parser::getPrimaryCommand(std::string userInput) {
	PrimaryCommandType primaryCommandType;
	try {
		primaryCommandType = parsePrimaryCommand(userInput);
	} catch (std::exception e) {
		primaryCommandType = PrimaryCommandType::Invalid;
	}
	return primaryCommandType;
}

void Parser::initialiseCommandTokeniser(PrimaryCommandType primaryCommandType) {
	// inclusion guard in calling function should have dealt with Invalid commands
	assert(primaryCommandType != PrimaryCommandType::Invalid);

	switch (primaryCommandType) {
		case Add:
			_commandTokeniser = new AddCommandTokeniser;
			break;
		case Complete:
			_commandTokeniser = new CompleteCommandTokeniser;
			break;
		case Delete:
			_commandTokeniser = new DeleteCommandTokeniser;
			break;
		case Display:
			_commandTokeniser = new DisplayCommandTokeniser;
			break;
		case Edit:
			_commandTokeniser = new EditCommandTokeniser;
			break;
		case Undo:
			_commandTokeniser = new UndoCommandTokeniser;
			break;
		default:
			// default should not be reached because of inclusion guard in
			// calling function and assertion in this function
			return;
	}
}

PrimaryCommandType Parser::parsePrimaryCommand(std::string userInput) {
	PrimaryCommandType commandType;

	if (isAddCommand(userInput)) {
		commandType = Add;
	} else if (isDeleteCommand(userInput)) {
		commandType = Delete;
	} else if (isDisplayCommand(userInput)) {
		commandType = Display;
	} else if (isEditCommand(userInput)) {
		commandType = Edit;
	} else if (isCompleteCommand(userInput)) {
		commandType = Complete;
	} else if (isUndoCommand(userInput)) {
		commandType = Undo;
	} else {
		throw CommandDoesNotExistException();
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
