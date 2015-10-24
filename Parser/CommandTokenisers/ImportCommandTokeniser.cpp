#include "ImportCommandTokeniser.h"

ImportCommandTokeniser::ImportCommandTokeniser(void) {
	// nothing
}

ImportCommandTokeniser::~ImportCommandTokeniser(void) {
	// nothing
}

CommandTokens ImportCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Import);

	if (isImportLocalCommand(userInput)) {
		tokeniseImportLocalCommand(userInput);
	}

	return _commandTokens;
}

bool ImportCommandTokeniser::isImportCommand(std::string userInput) {
	if (isImportLocalCommand(userInput)) {
		return true;
	}
	return false;
}

bool ImportCommandTokeniser::isImportLocalCommand(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("Import [^ ]+", std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void ImportCommandTokeniser::tokeniseImportLocalCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::None);

	std::smatch matchResults;
	std::regex_match(userInput,
	                 matchResults,
	                 std::regex("import ([^ ]+)", std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string importFilePath = matchResults[1];
	_commandTokens.setOtherCommandParameter(importFilePath);
}
