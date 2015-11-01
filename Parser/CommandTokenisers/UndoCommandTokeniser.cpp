//@@ author A0097681N
#include "UndoCommandTokeniser.h"

UndoCommandTokeniser::UndoCommandTokeniser(void) {
	// nothing here
}

UndoCommandTokeniser::~UndoCommandTokeniser(void) {
	// nothing here
}

bool UndoCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isUndoOnce(userInput)) {
		return true;
	}
	return false;
}

CommandTokens UndoCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Undo);

	if (isUndoOnce(userInput)) {
		tokeniseUndoOnce(&tokenisedCommand);
	}

	return tokenisedCommand;
}

bool UndoCommandTokeniser::isUndoOnce(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("UNDO",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void UndoCommandTokeniser::tokeniseUndoOnce(CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::None);
}
