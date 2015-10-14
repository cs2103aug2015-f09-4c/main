#include "EditCommandTokeniser.h"

EditCommandTokeniser::EditCommandTokeniser(void) {
	// nothing here
}

EditCommandTokeniser::~EditCommandTokeniser(void) {
	// nothing here
}

CommandTokens EditCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.resetMemberVariables();
	_commandTokens.setPrimaryCommand(PrimaryCommandType::Edit);

	if (isEditName(userInput)) {
		tokeniseEditNameCommand(userInput);
	} else if (isEditStartDate(userInput)) {
		tokeniseEditStartDateCommand(userInput);
	} else if (isEditEndDate(userInput)) {
		tokeniseEditEndDateCommand(userInput);
	}

	return _commandTokens;
}


bool EditCommandTokeniser::isEditEndDate(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("edit end [0-9]{1,} .{1,}",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool EditCommandTokeniser::isEditStartDate(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("edit start [0-9]{1,} .{1,}",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

bool EditCommandTokeniser::isEditName(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("edit name [0-9]{1,} .{1,}",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void EditCommandTokeniser::tokeniseEditEndDateCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::End);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("edit end ([0-9]{1,}) (.*)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	boost::posix_time::ptime endDate = parseUserInputDate(matchResults[2]);
	_commandTokens.setEndDateTime(endDate);
}

void EditCommandTokeniser::tokeniseEditStartDateCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Start);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("edit start ([0-9]{1,}) (.*)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	boost::posix_time::ptime startDate = parseUserInputDate(matchResults[2]);
	_commandTokens.setStartDateTime(startDate);
}

void EditCommandTokeniser::tokeniseEditNameCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(SecondaryCommandType::Name);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("edit name ([0-9]{1,}) (.*)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	int index = stoi(matchResults[1]);
	_commandTokens.setIndex(index);

	_commandTokens.setTaskName(matchResults[2]);

	// TODO: remove this when all using taskName
	std::vector<std::string> newDetails;
	newDetails.push_back(matchResults[2]);
	_commandTokens.setDetails(newDetails);
}
