//@@author A0097681N
#include "Parser.h"

#include "CommandTokenisers\AddCommandTokeniser.h"
#include "CommandTokenisers\ConfigureCommandTokeniser.h"
#include "CommandTokenisers\CompleteCommandTokeniser.h"
#include "CommandTokenisers\DeleteCommandTokeniser.h"
#include "CommandTokenisers\DisplayCommandTokeniser.h"
#include "CommandTokenisers\ExportCommandTokeniser.h"
#include "CommandTokenisers\EditCommandTokeniser.h"
#include "CommandTokenisers\ImportCommandTokeniser.h"
#include "CommandTokenisers\RefreshCommandTokeniser.h"
#include "CommandTokenisers\SearchCommandTokeniser.h"
#include "CommandTokenisers\SortCommandTokeniser.h"
#include "CommandTokenisers\TagCommandTokeniser.h"
#include "CommandTokenisers\UndoCommandTokeniser.h"
#include "CommandTokenisers\UntagCommandTokeniser.h"

Parser::Parser(void) {
	_logger = Logger::getInstance();

	initialiseAllCommandTokenisers();
	initialiseInvalidCommandTokens();
}

void Parser::initialiseAllCommandTokenisers() {
	_commandTokenisers.push_back(new AddCommandTokeniser);
	_commandTokenisers.push_back(new ConfigureCommandTokeniser);
	_commandTokenisers.push_back(new CompleteCommandTokeniser);
	_commandTokenisers.push_back(new DeleteCommandTokeniser);
	_commandTokenisers.push_back(new DisplayCommandTokeniser);
	_commandTokenisers.push_back(new ExportCommandTokeniser);
	_commandTokenisers.push_back(new EditCommandTokeniser);
	_commandTokenisers.push_back(new ImportCommandTokeniser);
	_commandTokenisers.push_back(new RefreshCommandTokeniser);
	_commandTokenisers.push_back(new SearchCommandTokeniser);
	_commandTokenisers.push_back(new SortCommandTokeniser);
	_commandTokenisers.push_back(new TagCommandTokeniser);
	_commandTokenisers.push_back(new UndoCommandTokeniser);
	_commandTokenisers.push_back(new UntagCommandTokeniser);
}

void Parser::initialiseInvalidCommandTokens() {
	_invalidCommandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Invalid);
	_invalidCommandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::None);
}

CommandTokens Parser::parse(std::string userInput) {
	_logger->logINFO("Parser::parse(std::string userInput):CommandTokens called with parameter userInput=\"" + userInput + "\"");

	CommandTokeniser* commandTokeniser = getCommandTokeniser(userInput);
	if (commandTokeniser == nullptr) {
		return _invalidCommandTokens;
	}
	return commandTokeniser->tokeniseUserInput(userInput);
}

CommandTokeniser* Parser::getCommandTokeniser(std::string userInput) {
	for (CommandTokeniser* commandTokeniser : _commandTokenisers) {
		if (commandTokeniser->canTokeniseUserInput(userInput)) {
			return commandTokeniser;
		}
	}
	return nullptr;
}
