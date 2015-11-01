//@@ author A0097681N
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
	return std::regex_match(userInput,
	                        std::regex("COMPLETE [0-9]+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void CompleteCommandTokeniser::tokeniseCompleteIndex(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("COMPLETE ([0-9]+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = std::stoi(matchResults[1]);
	outputCommandTokens->setIndex(index);
}
