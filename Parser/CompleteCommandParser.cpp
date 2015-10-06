#include "CompleteCommandParser.h"

CompleteCommandParser::CompleteCommandParser(void) {
	// nothing here
}

CommandTokens CompleteCommandParser::parse(std::string userInput) {
	_commandTokens.resetMemberVariables();
	_commandTokens.setPrimaryCommand(PrimaryCommandType::Complete);

	tokeniseCompleteCommand(userInput);
}

void CompleteCommandParser::tokeniseCompleteCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("complete ([0-9]{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	int index = std::stoi(matchResults[1]);
	_commandTokens.setIndex(index);
}