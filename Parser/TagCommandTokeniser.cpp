#include "TagCommandTokeniser.h"


TagCommandTokeniser::TagCommandTokeniser(void) {
	// nothing here
}

TagCommandTokeniser::~TagCommandTokeniser(void) {
	// nothing here
}


CommandTokens TagCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Tag);

	if (isTagIndexCommand(userInput)) {
		tokeniseTagIndexCommand(userInput);
	}

	return _commandTokens;
}

bool TagCommandTokeniser::isTagCommand(std::string userInput) {
	if (isTagIndexCommand(userInput)) {
		return true;
	}

	return false;
}

bool TagCommandTokeniser::isTagIndexCommand(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("tag [0-9]+( (#[^ ]+))+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void TagCommandTokeniser::tokeniseTagIndexCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("tag ([0-9]+) .*",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	tokeniseTags(userInput);
}

void TagCommandTokeniser::tokeniseTags(std::string userInput) {
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
