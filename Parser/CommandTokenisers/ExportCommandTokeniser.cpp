#include "ExportCommandTokeniser.h"


ExportCommandTokeniser::ExportCommandTokeniser(void) {
	// nothing here
}

ExportCommandTokeniser::~ExportCommandTokeniser(void) {
	// nothing here
}

CommandTokens ExportCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Export);

	if (isExportToLocalDiskCommand(userInput)) {
		tokeniseExportToLocalDiskCommand(userInput);
	}

	return _commandTokens;
}

bool ExportCommandTokeniser::isExportCommand(std::string userInput) {
	if (isExportToLocalDiskCommand(userInput)) {
		return true;
	}
	return false;
}

bool ExportCommandTokeniser::isExportToLocalDiskCommand(std::string userInput) {
	return std::regex_match(userInput, std::regex("export [^ ]+",
	                                              std::regex_constants::ECMAScript | std::regex_constants::icase));
}

void ExportCommandTokeniser::tokeniseExportToLocalDiskCommand(std::string userInput) {
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::None);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("export ([^ ]+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string exportPath = matchResults[1];
	_commandTokens.setOtherCommandParameter(exportPath);
}
