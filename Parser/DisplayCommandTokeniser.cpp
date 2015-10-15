#include "DisplayCommandTokeniser.h"

DisplayCommandTokeniser::DisplayCommandTokeniser(void) {
	// nothing here
}

DisplayCommandTokeniser::~DisplayCommandTokeniser(void) {
	// nothing here
}

CommandTokens DisplayCommandTokeniser::tokeniseUserInput(std::string userInput) {
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

void DisplayCommandTokeniser::tokeniseDisplayFloatingCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Floating);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("display floating (.{1,})",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void DisplayCommandTokeniser::tokeniseDisplayByCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("display by (.{1,})",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[1]));
}

void DisplayCommandTokeniser::tokeniseDisplayAllCommand() {
	_commandTokens.setSecondaryCommand(All);
}

void DisplayCommandTokeniser::tokeniseDisplayFromToCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("display from (.{1,}) to (.{1,})",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setStartDateTime(parseUserInputDate(matchResults[1]));
	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[2]));
}

void DisplayCommandTokeniser::tokeniseDisplayFromCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Start);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("display from (.{1,})",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setStartDateTime(parseUserInputDate(matchResults[1]));
}

bool DisplayCommandTokeniser::isDisplayFloating(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("display floating.*",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayBy(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("display by .{1,}",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

// returns true if userInput contains "iisplay all", followed by whitespaces;
// case-insensitive
bool DisplayCommandTokeniser::isDisplayAll(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("display all *",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

// returns true if userInput contains "from" and subsequently "to";
// case-insensitive
bool DisplayCommandTokeniser::isDisplayFromTo(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("display from .{1,} to .{1,}",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayFrom(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("display from .{1,}",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}
