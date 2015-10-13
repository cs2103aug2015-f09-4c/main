#include "AddCommandParser.h"

AddCommandParser::AddCommandParser(void) {
	// nothing here
}

AddCommandParser::~AddCommandParser(void) {
	// nothing here
}

CommandTokens AddCommandParser::tokeniseUserInput(std::string userInput) {
	_commandTokens.resetMemberVariables();
	_commandTokens.setPrimaryCommand(PrimaryCommandType::Add);

	if (hasTags(userInput)) {
		tokeniseTags(userInput);
		userInput = trimTags(userInput);
	}

	if (isAddActivityCommand(userInput)) {
		tokeniseAddActivityCommand(userInput);
	} else if (isAddTodoCommand(userInput)) {
		tokeniseAddTodoCommand(userInput);
	} else {
		tokeniseAddFloatingCommand(userInput);
	}

	return _commandTokens;
}

std::string AddCommandParser::trimTags(std::string userInput) {
	int endIndex = userInput.find("#");
	return userInput.substr(0, endIndex);
}

bool AddCommandParser::hasTags(std::string userInput) {
	return std::regex_match(userInput,
		std::regex(".+#.+",
		std::regex_constants::ECMAScript));
}

// returns true if userInput contains "from" and subsequently "to";
// case-insensitive
bool AddCommandParser::isAddActivityCommand(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("add .{1,} from .{1,} TO .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

// returns true if userInput contains "by"; case-insensitive
bool AddCommandParser::isAddTodoCommand(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("add .{1,} by .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

// extract taskName, startDateTime, and endDateTime; and call the setters on
// _commandTokens to set these three fields
void AddCommandParser::tokeniseAddActivityCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("add (.{1,}) from (.{1,}) TO (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	std::string taskName = matchResults[1];
	_commandTokens.setTaskName(taskName);

	std::vector< std::string > newDetails;
	newDetails.push_back(taskName);
	_commandTokens.setDetails(newDetails);

	_commandTokens.setStartDateTime(parseUserInputDate(matchResults[2]));
	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[3]));
}

// extract taskName, and endDateTime; and call the setters on _commandTokens
// to set these two fields
void AddCommandParser::tokeniseAddTodoCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("add (.{1,}) by (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	std::string taskName = matchResults[1];
	_commandTokens.setTaskName(taskName);

	std::vector< std::string > newDetails;
	newDetails.push_back(matchResults[1]);
	_commandTokens.setDetails(newDetails);

	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[2]));
}

// extract taskName; and call the setter on _commandTokens to set this field
void AddCommandParser::tokeniseAddFloatingCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Floating);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("add (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	std::string taskName = matchResults[1];
	_commandTokens.setTaskName(taskName);

	std::vector< std::string > newDetails;
	newDetails.push_back(matchResults[1]);
	_commandTokens.setDetails(newDetails);
}

void AddCommandParser::tokeniseTags(std::string userInput) {
	std::string regexString = " (#[^ ]{1,})";
	std::smatch matchResults;
	std::vector<std::string> newTags;

	while (std::regex_search(userInput, matchResults,
		std::regex(regexString,
		std::regex_constants::ECMAScript | std::regex_constants::icase))) {

			newTags.push_back(matchResults[1]);

			// continue the search in the right substring
			userInput = matchResults.suffix().str();
	}

	_commandTokens.setTags(newTags);
}