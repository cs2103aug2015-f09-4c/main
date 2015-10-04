#include "Parser.h"

// TODO: tidy regex to use icase

Parser::Parser(void) {
	CommandTokens _commandTokens;
}

CommandTokens Parser::parse(std::string userInput) {

	PrimaryCommandType primaryCommand = parsePrimaryCommand(userInput);
	_commandTokens.setPrimaryCommand(primaryCommand);

	switch (primaryCommand) {
	case Add:
		tokeniseAddCommand(userInput);
		break;
	case Delete:
		tokeniseDeleteCommand(userInput);
		break;
	case Edit:
		tokeniseEditCommand(userInput);
		break;
	case Display:
		tokeniseDisplayCommand(userInput);
		break;
	case Invalid:
		return _commandTokens;
	}

	return _commandTokens;
}

PrimaryCommandType Parser::parsePrimaryCommand(std::string userInput) {
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

void Parser::tokeniseAddCommand(std::string userInput) {
	if (isAddActivityTask(userInput)) {
		tokeniseActivityTask(userInput);
	} else if (isAddTodoTask(userInput)) {
		tokeniseTodoTask(userInput);
	} else {
		tokeniseFloatingTask(userInput);
	}
}

void Parser::tokeniseDeleteCommand(std::string userInput) {
	if (isDeleteAll(userInput)) {
		tokeniseDeleteAllCommand();
	} else if (isDeleteFromTo(userInput)) {
		tokeniseDeleteFromToCommand(userInput);
	} else if (isDeleteBy(userInput)) {
		tokeniseDeleteByCommand(userInput);
	} else if (isDeleteIndex(userInput)) {
		tokeniseDeleteIndex(userInput);
	}
}


void Parser::tokeniseEditCommand(std::string userInput) {
	if (isEditName(userInput)) {
		tokeniseEditNameCommand(userInput);
	} else if (isEditStartDate(userInput)) {
		tokeniseEditStartDateCommand(userInput);
	} else if (isEditEndDate(userInput)) {
		tokeniseEditEndDateCommand(userInput);
	}
}

void Parser::tokeniseEditEndDateCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::End);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("edit end (.{1,}) (.*)",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
		
	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	boost::posix_time::ptime endDate = parseDate(matchResults[2]);
	_commandTokens.setEndDateTime(endDate);
}

void Parser::tokeniseEditStartDateCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Start);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("edit start (.{1,}) (.*)",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
		
	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	boost::posix_time::ptime startDate = parseDate(matchResults[2]);
	_commandTokens.setStartDateTime(startDate);
}

void Parser::tokeniseEditNameCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Name);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("edit name (.{1,}) (.*)",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
		
	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	_commandTokens.setTaskName(matchResults[2]);

	// TODO: remove this when all using taskName
	std::vector< std::string > newDetails;
	newDetails.push_back(matchResults[2]);
	_commandTokens.setDetails(newDetails);
}

void Parser::tokeniseDeleteByCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("delete by (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
		
	_commandTokens.setEndDateTime(parseDate(matchResults[1]));
}

bool Parser::isDeleteBy(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("delete by .*",
		std::regex_constants::ECMAScript | std::regex_constants::icase));
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

void Parser::tokeniseDeleteAllCommand() {
	_commandTokens.setSecondaryCommand(All);
}

void Parser::tokeniseDeleteFromToCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("delete from (.{1,}) to (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	_commandTokens.setStartDateTime(parseDate(matchResults[1]));
	_commandTokens.setEndDateTime(parseDate(matchResults[2]));
}

void Parser::tokeniseDeleteIndex(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("delete ([0-9]{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);
}

void Parser::tokeniseDisplayCommand(std::string userInput) {
	if (isDisplayAll(userInput)) {
		tokeniseDisplayAllCommand();
	} else if (isDisplayFromTo(userInput)) {
		tokeniseDisplayFromToCommand(userInput);
	} else if (isDisplayBy(userInput)) {
		tokeniseDisplayByCommand(userInput);
	} else if (isDisplayFloating(userInput)) {
		tokeniseDisplayFloatingCommand(userInput);
	}
}

void Parser::tokeniseDisplayFloatingCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Floating);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("display floating (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

void Parser::tokeniseDisplayByCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("display by (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	_commandTokens.setEndDateTime(parseDate(matchResults[1]));
}

void Parser::tokeniseDisplayAllCommand() {
	_commandTokens.setSecondaryCommand(All);
}

void Parser::tokeniseDisplayFromToCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
		std::regex("Display from (.{1,}) to (.{1,})",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));

	_commandTokens.setStartDateTime(parseDate(matchResults[1]));
	_commandTokens.setEndDateTime(parseDate(matchResults[2]));
}

bool Parser::isDisplayFloating(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("Display floating .*",
		std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool Parser::isDisplayBy(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("Display by .*",
		std::regex_constants::ECMAScript | std::regex_constants::icase));
}


// returns true if userInput contains "iisplay all", followed by whitespaces;
// case-insensitive
bool Parser::isDisplayAll(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("Display all *",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

// returns true if userInput contains "from" and subsequently "to";
// case-insensitive
bool Parser::isDisplayFromTo(std::string userInput) {
	return std::regex_match(userInput,
		std::regex("Display from .{1,} to .{1,}",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
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
bool Parser::isAddActivityTask(std::string userInput) {
	return std::regex_match(userInput,
		std::regex(".* [F][R][O][M] .*[T][O] .*",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

// returns true if userInput contains "by"; case-insensitive
bool Parser::isAddTodoTask(std::string userInput) {
	return std::regex_match(userInput,
		std::regex(".* [B][Y] .*",
		std::regex_constants::ECMAScript | std::regex_constants::icase ));
}

// extract taskName, startDateTime, and endDateTime; and call the setters on
// _commandTokens to set these three fields
void Parser::tokeniseActivityTask(std::string userInput) {
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
void Parser::tokeniseTodoTask(std::string userInput) {
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
void Parser::tokeniseFloatingTask(std::string userInput) {
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