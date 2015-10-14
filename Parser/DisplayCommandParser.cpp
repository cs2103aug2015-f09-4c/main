#include "DisplayCommandParser.h"


DisplayCommandParser::DisplayCommandParser(void) {
	// nothing here
}

CommandTokens DisplayCommandParser::parse(std::string userInput) {
	_commandTokens.resetMemberVariables();
	_commandTokens.setPrimaryCommand(PrimaryCommandType::Display);

	if (isDisplayAll(userInput)) {
		tokeniseDisplayAllCommand();
	} else if (isDisplayFromTo(userInput)) {
		tokeniseDisplayFromToCommand(userInput);
	} else if (isDisplayFrom(userInput)) {
		tokeniseDisplayFromCommand(userInput);
	} else if (isDisplayBy(userInput)) {
		tokeniseDisplayByCommand(userInput);
	} else if (isDisplayFloating(userInput)) {
		tokeniseDisplayFloatingCommand(userInput);
	}

	return _commandTokens;
}

void DisplayCommandParser::tokeniseDisplayFloatingCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Floating);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("display floating (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

void DisplayCommandParser::tokeniseDisplayByCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("display by (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	_commandTokens.setEndDateTime(parseDate(matchResults[1]));
}

void DisplayCommandParser::tokeniseDisplayAllCommand() {
	_commandTokens.setSecondaryCommand(All);
}

void DisplayCommandParser::tokeniseDisplayFromToCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("display from (.{1,}) to (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	_commandTokens.setStartDateTime(parseDate(matchResults[1]));
	_commandTokens.setEndDateTime(parseDate(matchResults[2]));
}

void DisplayCommandParser::tokeniseDisplayFromCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Start);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("display from (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	_commandTokens.setStartDateTime(parseDate(matchResults[1]));
}

bool DisplayCommandParser::isDisplayFloating(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("display floating.*",
		std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandParser::isDisplayBy(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("display by .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase));
}

// returns true if userInput contains "iisplay all", followed by whitespaces;
// case-insensitive
bool DisplayCommandParser::isDisplayAll(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("display all *",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

// returns true if userInput contains "from" and subsequently "to";
// case-insensitive
bool DisplayCommandParser::isDisplayFromTo(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("display from .{1,} to .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

bool DisplayCommandParser::isDisplayFrom(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("display from .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

boost::posix_time::ptime DisplayCommandParser::parseDate(std::string dateString) {
	return _dateParser.parse(dateString);
}