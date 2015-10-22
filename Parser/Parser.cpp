#include <assert.h>
#include "Parser.h"

Parser::Parser(void) {
	_logger = Logger::getInstance();

	_commandTokeniser = nullptr;
	_invalidCommandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Invalid);
	_invalidCommandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::None);
}

CommandTokens Parser::parse(std::string userInput) {
	_logger->logINFO("Parsing user input: " + userInput);

	try {
		selectCommandTokeniser(userInput);
	}
	catch (CommandDoesNotExistException& e) {
		_logger->logINFO(e.what());
		return _invalidCommandTokens;
	}

	return _commandTokeniser->tokeniseUserInput(userInput);
}

void Parser::selectCommandTokeniser(std::string userInput) {
	CommandTokens::PrimaryCommandType commandType;

	if (isAddCommand(userInput)) {
		_commandTokeniser = &_addCommandTokeniser;
	} else if (isCompleteCommand(userInput)) {
		_commandTokeniser = &_completeCommandTokeniser;
	} else if (isDeleteCommand(userInput)) {
		_commandTokeniser = &_deleteCommandTokeniser;
	} else if (isDisplayCommand(userInput)) {
		_commandTokeniser = &_displayCommandTokeniser;
	} else if (isEditCommand(userInput)) {
		_commandTokeniser = &_editCommandTokeniser;
	} else if (isExportCommand(userInput)) {
		_commandTokeniser = &_exportCommandTokeniser;
	} else if (isRefreshCommand(userInput)) {
		_commandTokeniser = &_refreshCommandTokeniser;
	} else if (isTagCommand(userInput)) {
		_commandTokeniser = &_tagCommandTokeniser;
	} else if (isUndoCommand(userInput)) {
		_commandTokeniser = &_undoCommandTokeniser;
	} else if (isUntagCommand(userInput)) {
		_commandTokeniser = &_untagCommandTokeniser;
	} else {
		_commandTokeniser = nullptr;
		throw CommandDoesNotExistException();
	}
}

bool Parser::isAddCommand(std::string& userInput) {
	return AddCommandTokeniser::isAddCommand(userInput);
}

bool Parser::isCompleteCommand(std::string& userInput) {
	return CompleteCommandTokeniser::isCompleteCommand(userInput);
}

bool Parser::isDeleteCommand(std::string& userInput) {
	return DeleteCommandTokeniser::isDeleteCommand(userInput);
}

bool Parser::isDisplayCommand(std::string& userInput) {
	return DisplayCommandTokeniser::isDisplayCommand(userInput);
}

bool Parser::isEditCommand(std::string& userInput) {
	return EditCommandTokeniser::isEditCommand(userInput);
}

bool Parser::isExportCommand(std::string& userInput) {
	return ExportCommandTokeniser::isExportCommand(userInput);
}

bool Parser::isRefreshCommand(std::string& userInput) {
	return RefreshCommandTokeniser::isRefreshCommand(userInput);
}

bool Parser::isTagCommand(std::string& userInput) {
	return TagCommandTokeniser::isTagCommand(userInput);
}

bool Parser::isUndoCommand(std::string& userInput) {
	return UndoCommandTokeniser::isUndoCommand(userInput);
}

bool Parser::isUntagCommand(std::string& userInput) {
	return UntagCommandTokeniser::isUntagCommand(userInput);
}
