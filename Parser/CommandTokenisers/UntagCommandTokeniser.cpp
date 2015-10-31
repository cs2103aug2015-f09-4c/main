//@@ author A0097681N
#include "UntagCommandTokeniser.h"

UntagCommandTokeniser::UntagCommandTokeniser(void) {
	// nothing here
}

UntagCommandTokeniser::~UntagCommandTokeniser(void) {
	// nothing here
}

CommandTokens UntagCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Untag);

	if (isUntagIndexCommand(userInput)) {
		tokeniseUntagIndexCommand(userInput);
	}

	return _commandTokens;
}

bool UntagCommandTokeniser::isValidCommand(std::string userInput) {
	return isUntagCommand(userInput);
}

bool UntagCommandTokeniser::isUntagCommand(std::string userInput) {
	if (isUntagIndexCommand(userInput)) {
		return true;
	}
	return false;
}

bool UntagCommandTokeniser::isUntagIndexCommand(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("untag [0-9]+( (#[^ ]+))+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void UntagCommandTokeniser::tokeniseUntagIndexCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("untag ([0-9]+) .*",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	tokeniseTags(userInput);
}

void UntagCommandTokeniser::tokeniseTags(std::string userInput) {
	std::vector<std::string> newTags;

	std::smatch matchResults;
	while (std::regex_search(userInput, matchResults,
	                         std::regex(" (#[^ ]+)",
	                                    std::regex_constants::ECMAScript | std::regex_constants::icase))) {

		newTags.push_back(matchResults[1]);

		// continue the search in the right substring
		userInput = matchResults.suffix().str();
	}

	_commandTokens.setTags(newTags);
}
