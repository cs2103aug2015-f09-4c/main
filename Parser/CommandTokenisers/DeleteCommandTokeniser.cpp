//@@ author A0097681N
#include "DeleteCommandTokeniser.h"

DeleteCommandTokeniser::DeleteCommandTokeniser(void) {
	// nothing here
}

DeleteCommandTokeniser::~DeleteCommandTokeniser(void) {
	// nothing here
}

bool DeleteCommandTokeniser::canTokeniseUserInput(std::string userInput) {
	if (isDeleteAll(userInput) ||
		isDeleteCompleted(userInput) ||
		isDeleteIndex(userInput) ||
		isDeleteFromTo(userInput) ||
		isDeleteFrom(userInput) ||
		isDeleteBy(userInput)) {
		return true;
	}
	return false;
}

CommandTokens DeleteCommandTokeniser::tokeniseUserInput(::std::string userInput) {
	assert(canTokeniseUserInput(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Delete);

	if (isDeleteAll(userInput)) {
		tokeniseDeleteAll(&tokenisedCommand);
	} else if (isDeleteCompleted(userInput)) {
		tokeniseDeleteCompleted(userInput, &tokenisedCommand);
	} else if (isDeleteIndex(userInput)) {
		tokeniseDeleteIndex(userInput, &tokenisedCommand);
	} else if (isDeleteFromTo(userInput)) {
		tokeniseDeleteFromTo(userInput, &tokenisedCommand);
	} else if (isDeleteFrom(userInput)) {
		tokeniseDeleteFrom(userInput, &tokenisedCommand);
	} else if (isDeleteBy(userInput)) {
		tokeniseDeleteBy(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool DeleteCommandTokeniser::isDeleteAll(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DELETE ALL",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DeleteCommandTokeniser::isDeleteCompleted(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DELETE COMPLETED",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DeleteCommandTokeniser::isDeleteIndex(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DELETE [0-9]+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DeleteCommandTokeniser::isDeleteFromTo(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DELETE FROM .+ TO .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DeleteCommandTokeniser::isDeleteFrom(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DELETE FROM .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool DeleteCommandTokeniser::isDeleteBy(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("DELETE BY .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void DeleteCommandTokeniser::tokeniseDeleteAll(CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::All);
}

void DeleteCommandTokeniser::tokeniseDeleteCompleted(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Completed);
}

void DeleteCommandTokeniser::tokeniseDeleteIndex(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("DELETE ([0-9]+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	outputCommandTokens->setIndex(index);
}

void DeleteCommandTokeniser::tokeniseDeleteFromTo(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Timed);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("DELETE FROM (.+) TO (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	boost::posix_time::ptime startDateTime = parseUserInputDate(matchResults[1]);
	boost::posix_time::ptime endDateTime = parseUserInputDate(matchResults[2]);

	outputCommandTokens->setStartDateTime(startDateTime);
	outputCommandTokens->setEndDateTime(endDateTime);
}

void DeleteCommandTokeniser::tokeniseDeleteFrom(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Start);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("DELETE FROM (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	boost::posix_time::ptime startDateTime = parseUserInputDate(matchResults[1]);
	outputCommandTokens->setStartDateTime(startDateTime);
}

void DeleteCommandTokeniser::tokeniseDeleteBy(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Todo);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("DELETE BY (.+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	boost::posix_time::ptime endDateTime = parseUserInputDate(matchResults[1]);
	outputCommandTokens->setEndDateTime(endDateTime);
}
