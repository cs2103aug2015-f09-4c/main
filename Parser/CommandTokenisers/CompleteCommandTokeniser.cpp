//@@author A0097681N
#include "CompleteCommandTokeniser.h"

CompleteCommandTokeniser::CompleteCommandTokeniser(void) {
	// nothing here
}

CompleteCommandTokeniser::~CompleteCommandTokeniser(void) {
	// nothing here
}

bool CompleteCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isCompleteIndex(userInput)) {
		return true;
	}
	return false;
}

CommandTokens CompleteCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::MarkAsComplete);

	if (isCompleteIndex(userInput)) {
		tokeniseCompleteIndex(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool CompleteCommandTokeniser::isCompleteIndex(std::string userInput) {
	return isRegexMatch(&userInput, "COMPLETE [0-9]+");
}

void CompleteCommandTokeniser::tokeniseCompleteIndex(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults = getRegexMatches(&userInput, "COMPLETE ([0-9]+)");

	int index = std::stoi(matchResults[1]);
	outputCommandTokens->setIndex(index);
}
