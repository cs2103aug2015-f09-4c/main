#include "DeleteCommandParser.h"


DeleteCommandParser::DeleteCommandParser(void) {
	// nothing here
}

CommandTokens DeleteCommandParser::parse(std::string userInput) {
	_commandTokens.resetMemberVariables();
	_commandTokens.setPrimaryCommand(PrimaryCommandType::Delete);

	if (isDeleteAll(userInput)) {
		tokeniseDeleteAllCommand();
	} else if (isDeleteFromTo(userInput)) {
		tokeniseDeleteFromToCommand(userInput);
	} else if (isDeleteBy(userInput)) {
		tokeniseDeleteByCommand(userInput);
	} else if (isDeleteIndex(userInput)) {
		tokeniseDeleteIndex(userInput);
	}

	return _commandTokens;
}


void DeleteCommandParser::tokeniseDeleteByCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("delete by (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	_commandTokens.setEndDateTime(parseDate(matchResults[1]));
}

bool DeleteCommandParser::isDeleteBy(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("delete by .*",
		std::regex_constants::ECMAScript | std::regex_constants::icase));
}


// returns true if userInput contains "delete all", followed by whitespaces;
// case-insensitive
bool DeleteCommandParser::isDeleteAll(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("delete all *",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

// returns true if userInput contains "from" and subsequently "to";
// case-insensitive
bool DeleteCommandParser::isDeleteFromTo(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("delete from .{1,} to .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

bool DeleteCommandParser::isDeleteIndex(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("delete [0-9]{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

void DeleteCommandParser::tokeniseDeleteAllCommand() {
	_commandTokens.setSecondaryCommand(All);
}

void DeleteCommandParser::tokeniseDeleteFromToCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("delete from (.{1,}) to (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	_commandTokens.setStartDateTime(parseDate(matchResults[1]));
	_commandTokens.setEndDateTime(parseDate(matchResults[2]));
}

void DeleteCommandParser::tokeniseDeleteIndex(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("delete ([0-9]{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);
}

boost::posix_time::ptime DeleteCommandParser::parseDate(std::string dateString) {
	return _dateParser.parse(dateString);
}