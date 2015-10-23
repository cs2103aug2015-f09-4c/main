#include "SearchCommandTokeniser.h"


SearchCommandTokeniser::SearchCommandTokeniser(void) {
	// nothing
}


SearchCommandTokeniser::~SearchCommandTokeniser(void) {
	// nothing
}


CommandTokens SearchCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Search);

	if (isSearchNameCommand(userInput)) {
		tokeniseSearchNameCommand(userInput);
	} else if (isSearchStartBeforeCommand(userInput)) {
		tokeniseSearchStartBeforeCommand(userInput);
	} else if (isSearchStartAfterCommand(userInput)) {
		tokeniseSearchStartAfterCommand(userInput);
	} else if (isSearchEndBeforeCommand(userInput)) {
		tokeniseSearchEndBeforeCommand(userInput);
	} else if (isSearchEndAfterCommand(userInput)) {
		tokeniseSearchEndAfterCommand(userInput);
	} else if (isSearchTagsCommand(userInput)) {
		tokeniseSearchTagsCommand(userInput);
	}

	return _commandTokens;
}

bool SearchCommandTokeniser::isSearchCommand(std::string userInput) {
	if (isSearchNameCommand(userInput) ||
		isSearchStartBeforeCommand(userInput) ||
		isSearchStartAfterCommand(userInput) ||
		isSearchEndBeforeCommand(userInput) ||
		isSearchEndAfterCommand(userInput) ||
		isSearchTagsCommand(userInput)) {
		return true;
	}
	return false;
}

bool SearchCommandTokeniser::isSearchNameCommand(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("search name .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool SearchCommandTokeniser::isSearchStartBeforeCommand(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("search start before .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool SearchCommandTokeniser::isSearchStartAfterCommand(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("search start after .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool SearchCommandTokeniser::isSearchEndBeforeCommand(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("search end before .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool SearchCommandTokeniser::isSearchEndAfterCommand(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("search end after .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool SearchCommandTokeniser::isSearchTagsCommand(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("search tags( #[^ ])+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void SearchCommandTokeniser::tokeniseSearchNameCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Name);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("search name (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string taskNameToSearch = matchResults[1];
	_commandTokens.setTaskName(taskNameToSearch);
}

void SearchCommandTokeniser::tokeniseSearchStartBeforeCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::StartBefore);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("search start before (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setStartDateTime(parseUserInputDate(matchResults[1]));
}

void SearchCommandTokeniser::tokeniseSearchStartAfterCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::StartAfter);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("search start after (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setStartDateTime(parseUserInputDate(matchResults[1]));
}

void SearchCommandTokeniser::tokeniseSearchEndBeforeCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::EndBefore);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("search end before (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[1]));
}

void SearchCommandTokeniser::tokeniseSearchEndAfterCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::EndAfter);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("search end after (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[1]));
}

void SearchCommandTokeniser::tokeniseSearchTagsCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Tags);

	tokeniseTags(userInput);
}

void SearchCommandTokeniser::tokeniseTags(std::string userInput) {
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
