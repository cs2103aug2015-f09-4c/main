#include "Parser.h"

Parser::Parser(void) {
	CommandTokens _commandTokens;
}

CommandTokens Parser::parse(std::string userInput) {

	PrimaryCommandType primaryCommand = extractPrimaryCommand(userInput);
	_commandTokens.setPrimaryCommand(primaryCommand);

	switch (primaryCommand) {
	case Add:
		extractAddCommand(userInput);
		break;
	case Delete:
		extractDeleteCommand(userInput);
		break;
	case Edit:
		extractEditCommand(userInput);
		break;
	case Display:
		extractDisplayCommand(userInput);
		break;
	case Invalid:
		return _commandTokens;
	}

	return _commandTokens;
}

PrimaryCommandType Parser::extractPrimaryCommand(std::string userInput) {
	PrimaryCommandType commandType = Invalid;
	if (isAddCommand(userInput)) {
		commandType = Add;
	} else if (isDeleteCommand(userInput)) {
		commandType = Delete;
	} else if (isEditCommand(userInput)) {
		commandType = Edit;
	} else if (isDisplayCommand(userInput)) {
		commandType = Display;
	}
	return commandType;
}

void Parser::extractAddCommand(std::string userInput) {
	if (isActivityTask(userInput)) {
		extractActivityTask(userInput);
	} else if (isTodoTask(userInput)) {
		extractTodoTask(userInput);
	} else {
		extractFloatingTask(userInput);
	}
}

void Parser::extractDeleteCommand(std::string userInput) {
	if (isDeleteAll(userInput)) {
		extractDeleteAllCommand();
	} else if (isDeleteFromTo(userInput)) {
		extractDeleteFromToCommand(userInput);
	} /*else if (isDeleteBy(userInput)) {

	} else if (isDeleteFloating(userInput)) {

	}*/ else if (isDeleteIndex(userInput)) {
		extractDeleteIndex(userInput);
	}
}

// returns true if userInput contains "delete all", followed by whitespaces;
// case-insensitive
bool Parser::isDeleteAll(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("delete all *",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

// returns true if userInput contains "from" and subsequently "to";
// case-insensitive
bool Parser::isDeleteFromTo(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("delete from .{1,} to .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

bool Parser::isDeleteIndex(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("delete [0-9]{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

void Parser::extractDeleteAllCommand() {
	_commandTokens.setSecondaryCommand(All);
}

void Parser::extractDeleteFromToCommand(std::string userInput) {	
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("delete from (.{1,}) to (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	_commandTokens.setStartDateTime(parseDate(matchResults[1]));
	_commandTokens.setEndDateTime(parseDate(matchResults[2]));
}

void Parser::extractDeleteIndex(std::string userInput) {	
	// TODO: check if there is a secondary command type
	// _commandTokens.setSecondaryCommand(SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("delete ([0-9]{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	std::vector< std::string > newDetails;
	newDetails.push_back(matchResults[1]);
}

// TODO: implement
void Parser::extractEditCommand(std::string userInput) {
}

// TODO: implement
void Parser::extractDisplayCommand(std::string userInput) {
}

bool Parser::isAddCommand(std::string& userInput) {
	return std::regex_match(userInput,
	                        std::regex("[A][D][D] .*", std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool Parser::isDeleteCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("[Dd][Ee][Ll][Ee][Tt][Ee] .*"));
}

bool Parser::isEditCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("[Ee][Dd][Ii][Tt] .*"));
}

bool Parser::isDisplayCommand(std::string& userInput) {
	return std::regex_match(userInput, std::regex("[Dd][Ii][Ss][Pp][Ll][Aa][Yy] .*"));
}

// returns true if userInput contains "from" and subsequently "to";
// case-insensitive
bool Parser::isActivityTask(std::string userInput) {
	return std::regex_match(userInput,
		std::regex(".* [F][R][O][M] .*[T][O] .*",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

// returns true if userInput contains "by"; case-insensitive
bool Parser::isTodoTask(std::string userInput) {
	return std::regex_match(userInput,
		std::regex(".* [B][Y] .*",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

// extract taskName, startDateTime, and endDateTime; and call the setters on
// _commandTokens to set these three fields
void Parser::extractActivityTask(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("[A][D][D] (.*) [F][R][O][M] (.*) [T][O] (.*)",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	std::vector< std::string > newDetails;
	newDetails.push_back(matchResults[1]);
	_commandTokens.setDetails(newDetails);

	_commandTokens.setStartDateTime(parseDate(matchResults[2]));
	_commandTokens.setEndDateTime(parseDate(matchResults[3]));
}

// extract taskName, and endDateTime; and call the setters on _commandTokens
// to set these two fields
void Parser::extractTodoTask(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("[A][D][D] (.*) [B][Y] (.*)",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	std::vector< std::string > newDetails;
	newDetails.push_back(matchResults[1]);
	_commandTokens.setDetails(newDetails);

	_commandTokens.setEndDateTime(parseDate(matchResults[2]));
}

// extract taskName; and call the setter on _commandTokens to set this field
void Parser::extractFloatingTask(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Floating);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("[A][D][D] (.*)",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	std::vector< std::string > newDetails;
	newDetails.push_back(matchResults[1]);
	_commandTokens.setDetails(newDetails);
}

// TODO: implement natural language date processing
// convert date from string to ptime; currently only accepts standard date
// string
boost::posix_time::ptime Parser::parseDate(std::string dateString) {
	boost::posix_time::ptime ptimePlaceholder(boost::posix_time::time_from_string(dateString));
	return ptimePlaceholder;
}