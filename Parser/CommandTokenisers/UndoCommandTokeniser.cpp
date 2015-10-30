#include "UndoCommandTokeniser.h"

UndoCommandTokeniser::UndoCommandTokeniser(void) {
	// nothing here
}


UndoCommandTokeniser::~UndoCommandTokeniser(void) {
	// nothing here
}

CommandTokens UndoCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Undo);

	if (isUndoOnceCommand(userInput)) {
		tokeniseUndoOnceCommand();
	}

	return _commandTokens;
}

bool UndoCommandTokeniser::isValidCommand(std::string userInput) {
	return isUndoCommand(userInput);
}

bool UndoCommandTokeniser::isUndoCommand(std::string userInput) {
	if (isUndoOnceCommand(userInput)) {
		return true;
	}
	return false;
}

bool UndoCommandTokeniser::isUndoOnceCommand(std::string userInput) {
	return std::regex_match(userInput, std::regex("undo",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void UndoCommandTokeniser::tokeniseUndoOnceCommand() {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::None);
}
