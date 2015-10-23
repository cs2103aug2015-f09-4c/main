#include "RefreshCommandTokeniser.h"


RefreshCommandTokeniser::RefreshCommandTokeniser(void) {
	// nothing
}

RefreshCommandTokeniser::~RefreshCommandTokeniser(void) {
	// nothing
}

CommandTokens RefreshCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Refresh);

	if (isRefreshSimpliciterCommand(userInput)) {
		tokeniseRefreshSimpliciterCommand(userInput);
	}

	return _commandTokens;
}

bool RefreshCommandTokeniser::isRefreshCommand(std::string userInput) {
	if (isRefreshSimpliciterCommand(userInput)) {
		return true;
	}
	return false;
}

bool RefreshCommandTokeniser::isRefreshSimpliciterCommand(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("refresh",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void RefreshCommandTokeniser::tokeniseRefreshSimpliciterCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::None);
}
