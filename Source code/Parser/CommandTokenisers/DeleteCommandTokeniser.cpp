//@@author A0097681N
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
	return isRegexMatch(&userInput, "DELETE ALL");
}

bool DeleteCommandTokeniser::isDeleteCompleted(std::string userInput) {
	return isRegexMatch(&userInput, "DELETE COMPLETED");
}

bool DeleteCommandTokeniser::isDeleteIndex(std::string userInput) {
	return isRegexMatch(&userInput, "DELETE [0-9]+");
}

bool DeleteCommandTokeniser::isDeleteFromTo(std::string userInput) {
	return isRegexMatch(&userInput, "DELETE FROM .+ TO .+");
}

bool DeleteCommandTokeniser::isDeleteFrom(std::string userInput) {
	return isRegexMatch(&userInput, "DELETE FROM .+");
}

bool DeleteCommandTokeniser::isDeleteBy(std::string userInput) {
	return isRegexMatch(&userInput, "DELETE BY .+");
}

void DeleteCommandTokeniser::tokeniseDeleteAll(CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::All);
}

void DeleteCommandTokeniser::tokeniseDeleteCompleted(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Completed);
}

void DeleteCommandTokeniser::tokeniseDeleteIndex(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Index);

	std::smatch matchResults = getRegexMatches(&userInput, "DELETE ([0-9]+)");

	int index = stoi(matchResults[1]);
	outputCommandTokens->setIndex(index);
}

void DeleteCommandTokeniser::tokeniseDeleteFromTo(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::FromTo);

	std::smatch matchResults = getRegexMatches(&userInput, "DELETE FROM (.+) TO (.+)");

	boost::posix_time::ptime startDateTime = parseUserInputDate(matchResults[1]);
	boost::posix_time::ptime endDateTime = parseUserInputDate(matchResults[2]);

	outputCommandTokens->setStartDateTime(startDateTime);
	outputCommandTokens->setEndDateTime(endDateTime);
}

void DeleteCommandTokeniser::tokeniseDeleteFrom(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::Start);

	std::smatch matchResults = getRegexMatches(&userInput, "DELETE FROM (.+)");

	boost::posix_time::ptime startDateTime = parseUserInputDate(matchResults[1]);
	outputCommandTokens->setStartDateTime(startDateTime);
}

void DeleteCommandTokeniser::tokeniseDeleteBy(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::By);

	std::smatch matchResults = getRegexMatches(&userInput, "DELETE BY (.+)");

	boost::posix_time::ptime endDateTime = parseUserInputDate(matchResults[1]);
	outputCommandTokens->setEndDateTime(endDateTime);
}
