//@@author A0112218W

#include "Command_Export.h"

ExportCommand::ExportCommand(std::string filePath) : Command(CommandTokens::PrimaryCommandType::Export) {
	if (filePath.empty()) {
		throw COMMAND_CREATION_EXCEPTION(MESSAGE_EXPORT_INVALID_FILEPATH);
	}
	_filePath = filePath;
}

UIFeedback ExportCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	try {
		runTimeStorage -> saveToFile(_filePath);
	} catch (INVALID_FILE_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	} catch (INVALID_PATH_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	}
	postExecutionAction(runTimeStorage);

	char buffer[255];
	sprintf_s(buffer, MESSAGE_EXPORT_SUCCESS.c_str(), _filePath.c_str());
	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), std::string(buffer));
}

UIFeedback ExportCommand::undo() {
	assert(false);
	return UIFeedback();
}

bool ExportCommand::canUndo() {
	return false;
}

ExportCommand::~ExportCommand(void){
}
