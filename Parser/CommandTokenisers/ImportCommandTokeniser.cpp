#include "ImportCommandTokeniser.h"

ImportCommandTokeniser::ImportCommandTokeniser(void) {
	// nothing
}

ImportCommandTokeniser::~ImportCommandTokeniser(void) {
	// nothing
}

bool ImportCommandTokeniser::isValidCommand(std::string userInput) {
	if (isImportLocal(userInput)) {
		return true;
	}
	return false;
}

CommandTokens ImportCommandTokeniser::tokeniseUserInput(std::string userInput) {
	assert(isValidCommand(userInput));

	CommandTokens tokenisedCommand(CommandTokens::PrimaryCommandType::Import);

	if (isImportLocal(userInput)) {
		tokeniseImportLocal(userInput, &tokenisedCommand);
	}

	return tokenisedCommand;
}

bool ImportCommandTokeniser::isImportLocal(std::string userInput) {
	return std::regex_match(userInput,
	                        std::regex("IMPORT [^ ]+",
	                                   std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void ImportCommandTokeniser::tokeniseImportLocal(std::string userInput, CommandTokens* outputCommandTokens) {
	outputCommandTokens->setSecondaryCommand(CommandTokens::SecondaryCommandType::None);

	std::smatch matchResults;
	std::regex_match(userInput,
	                 matchResults,
	                 std::regex("IMPORT ([^ ]+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string importFilePath = matchResults[1];
	outputCommandTokens->setOtherCommandParameter(importFilePath);
}
