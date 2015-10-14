#include "DeleteCommandTokeniser.h"

DeleteCommandTokeniser::DeleteCommandTokeniser(void) {
	// nothing here
}

DeleteCommandTokeniser::~DeleteCommandTokeniser(void) {
	// nothing here
}

CommandTokens DeleteCommandTokeniser::tokeniseUserInput(::std::string userInput) {
	_commandTokens.resetMemberVariables();
	_commandTokens.setPrimaryCommand(PrimaryCommandType::Delete);

	if (isDeleteAll(userInput)) {
		tokeniseDeleteAllCommand();
	} else if (isDeleteFromTo(userInput)) {
		tokeniseDeleteFromToCommand(userInput);
	} else if (isDeleteFrom(userInput)) {
		tokeniseDeleteFromCommand(userInput);
	} else if (isDeleteBy(userInput)) {
		tokeniseDeleteByCommand(userInput);
	} else if (isDeleteIndex(userInput)) {
		tokeniseDeleteIndex(userInput);
	}

	return _commandTokens;
}


void DeleteCommandTokeniser::tokeniseDeleteByCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("delete by (.{1,})",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[1]));
}

bool DeleteCommandTokeniser::isDeleteBy(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("delete by .*",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}


// returns true if userInput contains "delete all", followed by whitespaces;
// case-insensitive
bool DeleteCommandTokeniser::isDeleteAll(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("delete all *",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

// returns true if userInput contains "from" and subsequently "to";
// case-insensitive
bool DeleteCommandTokeniser::isDeleteFromTo(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("delete from .{1,} to .{1,}",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DeleteCommandTokeniser::isDeleteFrom(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("delete from .{1,}",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DeleteCommandTokeniser::isDeleteIndex(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("delete [0-9]{1,}",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void DeleteCommandTokeniser::tokeniseDeleteAllCommand() {
	_commandTokens.setSecondaryCommand(All);
}

void DeleteCommandTokeniser::tokeniseDeleteFromToCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("delete from (.{1,}) to (.{1,})",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setStartDateTime(parseUserInputDate(matchResults[1]));
	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[2]));
}

void DeleteCommandTokeniser::tokeniseDeleteFromCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Start);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("delete from (.{1,})",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setStartDateTime(parseUserInputDate(matchResults[1]));
}

void DeleteCommandTokeniser::tokeniseDeleteIndex(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("delete ([0-9]{1,})",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);
}
