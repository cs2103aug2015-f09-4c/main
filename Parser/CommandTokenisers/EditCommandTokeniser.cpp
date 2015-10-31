//@@ author A0097681N
#include "EditCommandTokeniser.h"

EditCommandTokeniser::EditCommandTokeniser(void) {
	// nothing here
}

EditCommandTokeniser::~EditCommandTokeniser(void) {
	// nothing here
}

CommandTokens EditCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.reset();
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Edit);

	if (isEditName(userInput)) {
		tokeniseEditNameCommand(userInput);
	} else if (isEditStartDate(userInput)) {
		tokeniseEditStartDateCommand(userInput);
	} else if (isEditEndDate(userInput)) {
		tokeniseEditEndDateCommand(userInput);
	}

	return _commandTokens;
}

bool EditCommandTokeniser::isValidCommand(std::string userInput) {
	return isEditCommand(userInput);
}

bool EditCommandTokeniser::isEditCommand(std::string userInput) {
	if (isEditEndDate(userInput) ||
		isEditStartDate(userInput) ||
		isEditName(userInput)) {
		return true;
	}
	return false;
}

bool EditCommandTokeniser::isEditEndDate(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("edit end [0-9]+ .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool EditCommandTokeniser::isEditStartDate(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("edit start [0-9]+ .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool EditCommandTokeniser::isEditName(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("edit name [0-9]+ .+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void EditCommandTokeniser::tokeniseEditEndDateCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::End);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("edit end ([0-9]+) (.*)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	boost::posix_time::ptime endDate = parseUserInputDate(matchResults[2]);
	_commandTokens.setEndDateTime(endDate);
}

void EditCommandTokeniser::tokeniseEditStartDateCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Start);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("edit start ([0-9]+) (.*)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	boost::posix_time::ptime startDate = parseUserInputDate(matchResults[2]);
	_commandTokens.setStartDateTime(startDate);
}

void EditCommandTokeniser::tokeniseEditNameCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::Name);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("edit name ([0-9]+) (.*)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	_commandTokens.setTaskName(matchResults[2]);
}
