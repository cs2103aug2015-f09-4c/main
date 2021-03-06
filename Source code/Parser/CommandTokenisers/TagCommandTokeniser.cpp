//@@author A0097681N
#include "TagCommandTokeniser.h"

TagCommandTokeniser::TagCommandTokeniser(void) {
	// nothing here
}

TagCommandTokeniser::~TagCommandTokeniser(void) {
	// nothing here
}

bool TagCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isTagIndex(userInput)) {
		return true;
	}
	return false;
}

CommandTokens TagCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Tag);

	if (isTagIndex(userInput)) {
		tokeniseTagIndex(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool TagCommandTokeniser::isTagIndex(std::string userInput) {
	return isRegexMatch(&userInput, "TAG [0-9]+( (#[^ ]+))+");
}

void TagCommandTokeniser::tokeniseTagIndex(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults = getRegexMatches(&userInput, "TAG ([0-9]+) .*");

	int index = stoi(matchResults[1]);
	outputCommandTokens->setIndex(index);

	tokeniseTags(userInput, outputCommandTokens);
}

void TagCommandTokeniser::tokeniseTags(std::string userInput, CommandTokens* outputCommandTokens) {
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
