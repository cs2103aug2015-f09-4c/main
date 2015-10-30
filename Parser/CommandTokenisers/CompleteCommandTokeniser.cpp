#include "CompleteCommandTokeniser.h"

CompleteCommandTokeniser::CompleteCommandTokeniser(void) {
	// nothing here
}

CompleteCommandTokeniser::~CompleteCommandTokeniser(void) {
	// nothing here
}

CommandTokens CompleteCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.reset();
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Complete);

	tokeniseCompleteIndexCommand(userInput);
	return _commandTokens;
}

bool CompleteCommandTokeniser::isValidCommand(std::string userInput) {
	return isCompleteCommand(userInput);
}

bool CompleteCommandTokeniser::isCompleteCommand(std::string userInput) {
	if (isCompleteIndexCommand(userInput)) {
		return true;
	}
	return false;
}

bool CompleteCommandTokeniser::isCompleteIndexCommand(std::string userInput) {
	return std::regex_match(userInput, std::regex("complete [0-9]+",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void CompleteCommandTokeniser::tokeniseCompleteIndexCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("complete ([0-9]+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = std::stoi(matchResults[1]);
	_commandTokens.setIndex(index);
}
