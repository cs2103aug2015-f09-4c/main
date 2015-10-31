//@@ author A0097681N
#include "SearchCommandTokeniser.h"

SearchCommandTokeniser::SearchCommandTokeniser(void) {
	// nothing
}

SearchCommandTokeniser::~SearchCommandTokeniser(void) {
	// nothing
}

bool SearchCommandTokeniser::isValidCommand(std::string userInput) {
	if (isSearchName(userInput) ||
		isSearchStartBefore(userInput) ||
		isSearchStartAfter(userInput) ||
		isSearchEndBefore(userInput) ||
		isSearchEndAfter(userInput) ||
		isSearchTags(userInput)) {
		return true;
	}
	return false;
}

CommandTokens SearchCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(isValidCommand(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Search);

	if (isSearchName(userInput)) {
		tokeniseSearchName(userInput, &tokenisedCommand);
	} else if (isSearchStartBefore(userInput)) {
		tokeniseSearchStartBefore(userInput, &tokenisedCommand);
	} else if (isSearchStartAfter(userInput)) {
		tokeniseSearchStartAfter(userInput, &tokenisedCommand);
	} else if (isSearchEndBefore(userInput)) {
		tokeniseSearchEndBefore(userInput, &tokenisedCommand);
	} else if (isSearchEndAfter(userInput)) {
		tokeniseSearchEndAfter(userInput, &tokenisedCommand);
	} else if (isSearchTags(userInput)) {
		tokeniseSearchTags(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool SearchCommandTokeniser::isSearchName(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("SEARCH NAME .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool SearchCommandTokeniser::isSearchStartBefore(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("SEARCH START BEFORE .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool SearchCommandTokeniser::isSearchStartAfter(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("SEARCH START AFTER .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool SearchCommandTokeniser::isSearchEndBefore(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("SEARCH END BEFORE .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool SearchCommandTokeniser::isSearchEndAfter(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("SEARCH END AFTER .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool SearchCommandTokeniser::isSearchTags(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("SEARCH TAGS( #[^ ]+)+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void SearchCommandTokeniser::tokeniseSearchName(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Name);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("SEARCH NAME (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string taskNameToSearch = matchResults[1];
	outputCommandTokens->setTaskName(taskNameToSearch);
}

void SearchCommandTokeniser::tokeniseSearchStartBefore(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::StartBefore);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("SEARCH START BEFORE (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	boost::posix_time::ptime startDateTime = parseUserInputDate(matchResults[1]);
	outputCommandTokens->setStartDateTime(startDateTime);
}

void SearchCommandTokeniser::tokeniseSearchStartAfter(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::StartAfter);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("SEARCH START AFTER (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	boost::posix_time::ptime startDateTime = parseUserInputDate(matchResults[1]);
	outputCommandTokens->setStartDateTime(startDateTime);
}

void SearchCommandTokeniser::tokeniseSearchEndBefore(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::EndBefore);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("SEARCH END BEFORE (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	boost::posix_time::ptime endDateTime = parseUserInputDate(matchResults[1]);
	outputCommandTokens->setEndDateTime(endDateTime);
}

void SearchCommandTokeniser::tokeniseSearchEndAfter(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::EndAfter);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("SEARCH END AFTER (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	boost::posix_time::ptime endDateTime = parseUserInputDate(matchResults[1]);
	outputCommandTokens->setEndDateTime(endDateTime);
}

void SearchCommandTokeniser::tokeniseSearchTags(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Tags);

	std::vector<std::string> tokenisedTags;
	std::smatch matchResults;
	while (std::regex_search(userInput, matchResults,
	                         std::regex(" (#[^ ]+)",
	                                    std::regex_constants::ECMAScript | std::regex_constants::icase))) {

		tokenisedTags.push_back(matchResults[1]);

		// continue the search in the right substring
		userInput = matchResults.suffix().str();
	}

	outputCommandTokens->setTags(tokenisedTags);
}
