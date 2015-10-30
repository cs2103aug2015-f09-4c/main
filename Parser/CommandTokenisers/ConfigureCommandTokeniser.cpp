#include "ConfigureCommandTokeniser.h"

ConfigureCommandTokeniser::ConfigureCommandTokeniser(void) {
	// nothing here
}

ConfigureCommandTokeniser::~ConfigureCommandTokeniser(void) {
	// nothing here
}

bool ConfigureCommandTokeniser::isValidCommand(std::string userInput) {
	return isConfigureCommand(userInput);
}

bool ConfigureCommandTokeniser::isConfigureCommand(std::string userInput) {
	if (isConfigureSaveLocation(userInput)) {
		return true;
	}
	return false;
}

CommandTokens ConfigureCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Configure);

	if (isConfigureSaveLocation(userInput)) {
		tokeniseConfigureSaveLocation(userInput);
	}

	return _commandTokens;
}

bool ConfigureCommandTokeniser::isConfigureSaveLocation(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("Configure Save Location [^ ]+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void ConfigureCommandTokeniser::tokeniseConfigureSaveLocation(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::SaveLocation);

	std::smatch matchResults;

	std::regex_match(userInput,
	                 std::regex("Configure Save Location ([^ ]+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string saveLocation = matchResults[1];
	_commandTokens.setOtherCommandParameter(saveLocation);
}
