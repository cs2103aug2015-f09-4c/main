#include "AddCommandParser.h"

AddCommandParser::AddCommandParser(void) {
	// nothing here
}

CommandTokens AddCommandParser::parse(std::string userInput) {
	_commandTokens.resetMemberVariables();
	_commandTokens.setPrimaryCommand(PrimaryCommandType::Add);

	if (isAddActivityCommand(userInput)) {
		tokeniseAddActivityCommand(userInput);
	} else if (isAddTodoCommand(userInput)) {
		tokeniseAddTodoCommand(userInput);
	} else {
		tokeniseAddFloatingCommand(userInput);
	}

	return _commandTokens;
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

	_commandTokens.setStartDateTime(parseDate(matchResults[2]));
	_commandTokens.setEndDateTime(parseDate(matchResults[3]));
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

	_commandTokens.setEndDateTime(parseDate(matchResults[2]));
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

boost::posix_time::ptime AddCommandParser::parseDate(std::string dateString) {
	return _dateParser.parse(dateString);
}