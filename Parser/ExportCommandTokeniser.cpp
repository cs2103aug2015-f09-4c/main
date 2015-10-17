#include "ExportCommandTokeniser.h"


ExportCommandTokeniser::ExportCommandTokeniser(void) {
	// nothing here
}

ExportCommandTokeniser::~ExportCommandTokeniser(void) {
	// nothing here
}

CommandTokens ExportCommandTokeniser::tokeniseUserInput(std::string userInput) {
	_commandTokens.setPrimaryCommand(CommandTokens::PrimaryCommandType::Export);
	tokeniseExportCommand(userInput);

	return _commandTokens;
}

void ExportCommandTokeniser::tokeniseExportCommand(std::string userInput) {
	// secondaryCommandType set here so as not to interfere with future
	// extension; e.g., maybe there'l be an export to cloud function, and the
	// secondaryCommandType will not be None
	_commandTokens.setSecondaryCommand(CommandTokens::SecondaryCommandType::None);

	std::smatch matchResults;
	std::regex_match(userInput, matchResults,
	                 std::regex("export ([^ ]+)",
	                            std::regex_constants::ECMAScript | std::regex_constants::icase));

	std::string exportPath = matchResults[1];
	_commandTokens.setOtherCommandParameter(exportPath);
}
