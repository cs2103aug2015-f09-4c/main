#include <assert.h>
#include "Parser.h"
#include "AddCommandTokeniser.h"
#include "CompleteCommandTokeniser.h"
#include "DeleteCommandTokeniser.h"
#include "DisplayCommandTokeniser.h"
#include "ExportCommandTokeniser.h"
#include "EditCommandTokeniser.h"
#include "UndoCommandTokeniser.h"

Parser::Parser(void) {
	_logger = Logger::getInstance();

	_commandTokeniser = nullptr;
	_invalidCommandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Invalid);
	_invalidCommandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::None);
}

CommandTokens Parser::parse(std::string userInput) {
	_logger->logINFO("Parsing user input: " + userInput);

	// inclusion guard
	CommandTokens::PrimaryCommandType primaryCommandType = getPrimaryCommand(userInput);
	if (primaryCommandType == CommandTokens::PrimaryCommandType::Invalid) {
		return _invalidCommandTokens;
	}

	initialiseCommandTokeniser(primaryCommandType);

	return _commandTokeniser->tokeniseUserInput(userInput);
}

CommandTokens::PrimaryCommandType Parser::getPrimaryCommand(std::string userInput) {
	CommandTokens::PrimaryCommandType primaryCommandType;
	try {
		primaryCommandType = parsePrimaryCommand(userInput);
	} catch (std::exception e) {
		primaryCommandType = CommandTokens::PrimaryCommandType::Invalid;
	}
	return primaryCommandType;
}

void Parser::initialiseCommandTokeniser(CommandTokens::PrimaryCommandType primaryCommandType) {
	// inclusion guard in calling function should have dealt with Invalid commands
	assert(primaryCommandType != CommandTokens::PrimaryCommandType::Invalid);

	switch (primaryCommandType) {
		case CommandTokens::PrimaryCommandType::Add:
			_commandTokeniser = new AddCommandTokeniser;
			break;
		case CommandTokens::PrimaryCommandType::Complete:
			_commandTokeniser = new CompleteCommandTokeniser;
			break;
		case CommandTokens::PrimaryCommandType::Delete:
			_commandTokeniser = new DeleteCommandTokeniser;
			break;
		case CommandTokens::PrimaryCommandType::Display:
			_commandTokeniser = new DisplayCommandTokeniser;
			break;
		case CommandTokens::PrimaryCommandType::Edit:
			_commandTokeniser = new EditCommandTokeniser;
			break;
		case CommandTokens::PrimaryCommandType::Export:
			_commandTokeniser = new ExportCommandTokeniser;
			break;
		case CommandTokens::PrimaryCommandType::Undo:
			_commandTokeniser = new UndoCommandTokeniser;
			break;
		default:
			// default should not be reached because of inclusion guard in
			// calling function and assertion in this function
			return;
	}
}

CommandTokens::PrimaryCommandType Parser::parsePrimaryCommand(std::string userInput) {
	CommandTokens::PrimaryCommandType commandType;

	if (isAddCommand(userInput)) {
		commandType = CommandTokens::PrimaryCommandType::Add;
	} else if (isDeleteCommand(userInput)) {
		commandType = CommandTokens::PrimaryCommandType::Delete;
	} else if (isDisplayCommand(userInput)) {
		commandType = CommandTokens::PrimaryCommandType::Display;
	} else if (isEditCommand(userInput)) {
		commandType = CommandTokens::PrimaryCommandType::Edit;
	} else if (isExportCommand(userInput)) {
		commandType = CommandTokens::PrimaryCommandType::Export;
	} else if (isCompleteCommand(userInput)) {
		commandType = CommandTokens::PrimaryCommandType::Complete;
	} else if (isUndoCommand(userInput)) {
		commandType = CommandTokens::PrimaryCommandType::Undo;
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

bool Parser::isExportCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("export [^ ]+",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool Parser::isUndoCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("undo",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}
