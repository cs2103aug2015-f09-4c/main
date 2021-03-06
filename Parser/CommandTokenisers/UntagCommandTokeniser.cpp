//@@author A0097681N
#include "UntagCommandTokeniser.h"

UntagCommandTokeniser::UntagCommandTokeniser(void) {
	// nothing here
}

UntagCommandTokeniser::~UntagCommandTokeniser(void) {
	// nothing here
}

bool UntagCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isUntagIndex(userInput)) {
		return true;
	}
	return false;
}

CommandTokens UntagCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Untag);

	if (isUntagIndex(userInput)) {
		tokeniseUntagIndex(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool UntagCommandTokeniser::isUntagIndex(std::string userInput) {
	return isRegexMatch(&userInput, "UNTAG [0-9]+( (#[^ ]+))+");
}

void UntagCommandTokeniser::tokeniseUntagIndex(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults = getRegexMatches(&userInput, "UNTAG ([0-9]+) .*");

	int index = stoi(matchResults[1]);
	outputCommandTokens->setIndex(index);

	tokeniseTags(userInput, outputCommandTokens);
}

void UntagCommandTokeniser::tokeniseTags(std::string userInput, CommandTokens* outputCommandTokens) {
	std::vector<std::string> newTags;
	std::smatch matchResults;
	while (std::regex_search(userInput, matchResults,
	                         std::regex(" (#[^ ]+)",
	                                    std::regex_constants::ECMAScript | std::regex_constants::icase))) {

		newTags.push_back(matchResults[1]);

		// continue the search in the right substring
		userInput = matchResults.suffix().str();
	}

	outputCommandTokens->setTags(newTags);
}
