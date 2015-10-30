#include "AddCommandTokeniser.h"

AddCommandTokeniser::AddCommandTokeniser(void) {
	// nothing here
}

AddCommandTokeniser::~AddCommandTokeniser(void) {
	// nothing here
}

bool AddCommandTokeniser::isValidCommand(std::string userInput) {
	if (isAddFromTo(userInput) ||
		isAddBy(userInput) ||
		isAddFloating(userInput)) {
		return true;
	}
	return false;
}

CommandTokens AddCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(isValidCommand(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Add);

	if (isTagged(userInput)) {
		tokeniseTags(userInput, &tokenisedCommand);
		userInput = trimTags(userInput);
	}

	if (isAddFromTo(userInput)) {
		tokeniseAddFromTo(userInput, &tokenisedCommand);
	} else if (isAddBy(userInput)) {
		tokeniseAddBy(userInput, &tokenisedCommand);
	} else if (isAddFloating(userInput)) {
		tokeniseAddFloating(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool AddCommandTokeniser::isTagged(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex(".+?( #[^ ]+)+",
	                                   std::regex_constants::ECMAScript));
}

void AddCommandTokeniser::tokeniseTags(std::string userInput, CommandTokens* tokenisedCommand) {
	std::vector<std::string> newTags;

	std::smatch matchResults;
	while (std::regex_search(userInput, matchResults,
	                         std::regex(" (#[^ ]+)",
	                                    std::regex_constants::ECMAScript))) {

		newTags.push_back(matchResults[1]);

		// continue the search in the right substring
		userInput = matchResults.suffix().str();
	}

	tokenisedCommand->setTags(newTags);
}

std::string AddCommandTokeniser::trimTags(std::string userInput) {
	int endIndex = userInput.find(" #");
	return userInput.substr(0, endIndex);
}

bool AddCommandTokeniser::isAddFromTo(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("ADD .+ FROM .+ TO .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool AddCommandTokeniser::isAddBy(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("ADD .+ BY .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool AddCommandTokeniser::isAddFloating(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("ADD .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void AddCommandTokeniser::tokeniseAddFromTo(std::string userInput, CommandTokens* tokenisedCommand) {
	tokenisedCommand->setSecondaryCommand(CommandTokens::SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("ADD (.+) FROM (.+) TO (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string taskName = matchResults[1];
	boost::posix_time::ptime startDateTime = parseUserInputDate(matchResults[2]);
	boost::posix_time::ptime endDateTime = parseUserInputDate(matchResults[3]);

	tokenisedCommand->setTaskName(taskName);
	tokenisedCommand->setStartDateTime(startDateTime);
	tokenisedCommand->setEndDateTime(endDateTime);
}

void AddCommandTokeniser::tokeniseAddBy(std::string userInput, CommandTokens* tokenisedCommand) {
	tokenisedCommand->setSecondaryCommand(CommandTokens::SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("ADD (.+) BY (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string taskName = matchResults[1];
	boost::posix_time::ptime endDateTime = parseUserInputDate(matchResults[2]);

	tokenisedCommand->setTaskName(taskName);
	tokenisedCommand->setEndDateTime(endDateTime);
}

void AddCommandTokeniser::tokeniseAddFloating(std::string userInput, CommandTokens* tokenisedCommand) {
	tokenisedCommand->setSecondaryCommand(CommandTokens::SecondaryCommandType::Floating);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("ADD (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string taskName = matchResults[1];
	tokenisedCommand->setTaskName(taskName);
}
