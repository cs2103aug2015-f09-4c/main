//@@ author A0097681N
#include "DisplayCommandTokeniser.h"

DisplayCommandTokeniser::DisplayCommandTokeniser(void) {
	// nothing here
}

DisplayCommandTokeniser::~DisplayCommandTokeniser(void) {
	// nothing here
}

CommandTokens DisplayCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.reset();
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Display);

	if (isDisplayAll(userInput)) {
		tokeniseDisplayAllCommand();
	} else if (isDisplayFromTo(userInput)) {
		tokeniseDisplayFromToCommand(userInput);
	} else if (isDisplayFrom(userInput)) {
		tokeniseDisplayFromCommand(userInput);
	} else if (isDisplayBy(userInput)) {
		tokeniseDisplayByCommand(userInput);
	} else if (isDisplayFloating(userInput)) {
		tokeniseDisplayFloatingCommand();
	}

	return _commandTokens;
}

void DisplayCommandTokeniser::tokeniseDisplayFloatingCommand() {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Floating);
}

void DisplayCommandTokeniser::tokeniseDisplayByCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("display by (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[1]));
}

void DisplayCommandTokeniser::tokeniseDisplayAllCommand() {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::All);
}

void DisplayCommandTokeniser::tokeniseDisplayFromToCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("display from (.+) to (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setStartDateTime(parseUserInputDate(matchResults[1]));
	_commandTokens.setEndDateTime(parseUserInputDate(matchResults[2]));
}

void DisplayCommandTokeniser::tokeniseDisplayFromCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Start);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("display from (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	_commandTokens.setStartDateTime(parseUserInputDate(matchResults[1]));
}

bool DisplayCommandTokeniser::isValidCommand(std::string userInput) {
	return isDisplayCommand(userInput);
}

bool DisplayCommandTokeniser::isDisplayCommand(std::string userInput) {
	if (isDisplayFloating(userInput) ||
		isDisplayBy(userInput) ||
		isDisplayAll(userInput) ||
		isDisplayFromTo(userInput) ||
		isDisplayFrom(userInput)) {
		return true;
	}
	return false;
}

bool DisplayCommandTokeniser::isDisplayFloating(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("display floating",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayBy(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("display by .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

// returns true if userInput contains "display all", followed by whitespaces;
// case-insensitive
bool DisplayCommandTokeniser::isDisplayAll(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("display all",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

// returns true if userInput contains "from" and subsequently "to";
// case-insensitive
bool DisplayCommandTokeniser::isDisplayFromTo(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("display from .+ to .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DisplayCommandTokeniser::isDisplayFrom(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("display from .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}
