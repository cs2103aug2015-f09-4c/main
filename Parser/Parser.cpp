#include "Parser.h"

Parser::Parser(void) {
	CommandTokens _commandTokens;
}

CommandTokens Parser::parse(std::string userInput) {

	PrimaryCommandType primaryCommand = extractPrimaryCommand(userInput);
	_commandTokens.setPrimaryCommand(primaryCommand);

	switch (primaryCommand) {
	case Add:
		extractAddCommand(userInput);/*
	case Delete:
		extractDeleteCommand(userInput);
	case Edit:
		extractEditCommand(userInput);
	case Display:
		extractDisplayCommand(userInput);
	case Invalid:*/
	}

	return _commandTokens;
}

PrimaryCommandType Parser::extractPrimaryCommand(std::string userInput) {
	PrimaryCommandType commandType = Invalid;
	if (std::regex_match(userInput,
		std::regex("[A][D][D] .*",std::regex_constants::ECMAScript | std::regex_constants::icase ))) {
		commandType = Add;

	}/* else if (std::regex_match(userInput, std::regex("[Dd][Ee][Ll][Ee][Tt][Ee] .*"))) {
		commandType = Delete;

	} else if (std::regex_match(userInput, std::regex("[Ee][Dd][Ii][Tt] .*"))) {
		commandType = Edit;

	} else if (std::regex_match(userInput, std::regex("[Dd][Ii][Ss][Pp][Ll][Aa][Yy] .*"))) {
		commandType = Display;
	}*/
	return commandType;
}

void Parser::extractAddCommand(std::string userInput) {
	if (hasStartAndEndDate(userInput)) {
		extractAddCommandWithStartAndEndDate(userInput);
	} else if (hasEndDate(userInput)) {
		extractAddCommandWithEndDate(userInput);
	} else {
		extractAddCommandFloating(userInput);
	}
}

bool Parser::hasStartAndEndDate(std::string userInput) {
	return std::regex_match(userInput, std::regex(".* [Ff][Rr][Oo][Mm] .*[Tt][Oo] .*"));
}

bool Parser::hasEndDate(std::string userInput) {
	return std::regex_match(userInput, std::regex(".* [Bb][Yy] .*"));
}

void Parser::extractAddCommandWithStartAndEndDate(std::string userInput) {
	std::smatch matchResults;
	std::regex_match(userInput, matchResults, std::regex("[Aa][Dd][Dd] (.*) [Ff][Rr][Oo][Mm] (.*) [Tt][Oo] (.*)"));

	_commandTokens.setTaskName(matchResults[1]);
	_commandTokens.setStartDateTime(parseDate(matchResults[2]));
	_commandTokens.setEndDateTime(parseDate(matchResults[3]));
}

void Parser::extractAddCommandWithEndDate(std::string userInput) {
	std::smatch matchResults;
	std::regex_match(userInput, matchResults, std::regex("[Aa][Dd][Dd] (.*) [Bb][Yy] (.*)"));
}

void Parser::extractAddCommandFloating(std::string userInput) {
	std::smatch matchResults;
	std::regex_match(userInput, matchResults, std::regex("[Aa][Dd][Dd] (.*)"));
}

int Parser::parseDate(std::string dateString) {
	// TODO implement properly
	int dateInt = 20150927;
	return dateInt;
}