#include "CompleteCommandTokeniser.h"

CompleteCommandTokeniser::CompleteCommandTokeniser(void) {
	// nothing here
}

CompleteCommandTokeniser::~CompleteCommandTokeniser(void) {
	// nothing here
}

CommandTokens CompleteCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.resetMemberVariables();
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Complete);

	tokeniseCompleteCommand(userInput);
	return _commandTokens;
}

void CompleteCommandTokeniser::tokeniseCompleteCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("complete ([0-9]{1,})",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = std::stoi(matchResults[1]);
	_commandTokens.setIndex(index);
}
