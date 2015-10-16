#include "UndoCommandTokeniser.h"

UndoCommandTokeniser::UndoCommandTokeniser(void) {
	// nothing here
}


UndoCommandTokeniser::~UndoCommandTokeniser(void) {
	// nothing here
}

CommandTokens UndoCommandTokeniser::tokeniseUserInput(std::string userInput) {
	// currently only supports one undo command, no tokenising needed
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Undo);
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::None);

	return _commandTokens;
}
