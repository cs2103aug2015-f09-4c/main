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
	_commandTokens.resetMemberVariables();
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Add);

	if (hasTags(userInput)) {
		tokeniseTags(userInput);
		userInput = trimTags(userInput);
	}

	if (isAddFromTo(userInput)) {
		tokeniseAddActivityCommand(userInput);
	} else if (isAddBy(userInput)) {
		tokeniseAddTodoCommand(userInput);
	} else if (isAddFloating(userInput)) {
		tokeniseAddFloatingCommand(userInput);
	}

	return _commandTokens;
}

std::string AddCommandTokeniser::trimTags(std::string userInput) {
	int endIndex = userInput.find(" #");
	return userInput.substr(0, endIndex);
}

bool AddCommandTokeniser::hasTags(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex(".+?( #[^ ]+)+",
	                                   std::regex_constants::ECMAScript));
}

// returns true if userInput contains "from" and subsequently "to";
// case-insensitive
bool AddCommandTokeniser::isAddFromTo(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("add .+ from .+ to .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

// returns true if userInput contains "by"; case-insensitive
bool AddCommandTokeniser::isAddBy(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("add .+ by .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

// returns true if userInput contains "by"; case-insensitive
bool AddCommandTokeniser::isAddFloating(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("add .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

// extract taskName, startDateTime, and endDateTime; and call the setters on
// _commandTokens to set these three fields
void AddCommandTokeniser::tokeniseAddActivityCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("add (.+) from (.+) TO (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string taskName = matchResults[1];
	_commandTokens.setTaskName(taskName);

	_commandTokens.setStartDateTime(parseUserInputDate(matchResults[2]));
	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[3]));
}

// extract taskName, and endDateTime; and call the setters on _commandTokens
// to set these two fields
void AddCommandTokeniser::tokeniseAddTodoCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("add (.+) by (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string taskName = matchResults[1];
	_commandTokens.setTaskName(taskName);

	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[2]));
}

// extract taskName; and call the setter on _commandTokens to set this field
void AddCommandTokeniser::tokeniseAddFloatingCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Floating);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("add (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string taskName = matchResults[1];
	_commandTokens.setTaskName(taskName);
}

void AddCommandTokeniser::tokeniseTags(std::string userInput) {
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
