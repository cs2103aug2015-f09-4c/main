//@@ author A0097681N
#include "RefreshCommandTokeniser.h"

RefreshCommandTokeniser::RefreshCommandTokeniser(void) {
	// nothing
}

RefreshCommandTokeniser::~RefreshCommandTokeniser(void) {
	// nothing
}

bool RefreshCommandTokeniser::isValidCommand(std::string userInput) {
	if (isRefreshBasic(userInput)) {
		return true;
	}
	return false;
}

CommandTokens RefreshCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(isValidCommand(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Refresh);

	if (isRefreshBasic(userInput)) {
		tokeniseRefreshBasic(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool RefreshCommandTokeniser::isRefreshBasic(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("REFRESH",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void RefreshCommandTokeniser::tokeniseRefreshBasic(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::None);
}
