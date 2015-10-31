//@@ author A0097681N
#include "CompleteCommandTokeniser.h"

CompleteCommandTokeniser::CompleteCommandTokeniser(void) {
	// nothing here
}

CompleteCommandTokeniser::~CompleteCommandTokeniser(void) {
	// nothing here
}

bool CompleteCommandTokeniser::isValidCommand(std::string userInput) {
	if (isCompleteIndex(userInput)) {
		return true;
	}
	return false;
}

CommandTokens CompleteCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.reset();
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Complete);

	if (isCompleteIndex(userInput)) {
		tokeniseCompleteIndex(userInput);
	}

	return _commandTokens;
}

bool CompleteCommandTokeniser::isCompleteIndex(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("complete [0-9]+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void CompleteCommandTokeniser::tokeniseCompleteIndex(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("complete ([0-9]+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = std::stoi(matchResults[1]);
	_commandTokens.setIndex(index);
}
