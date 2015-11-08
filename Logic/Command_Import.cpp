//@@author A0112218W

#include "Command_Import.h"

ImportCommand::ImportCommand(std::string filePath) : Command(CommandTokens::PrimaryCommandType::Import) {
	if (filePath.empty()) {
		throw COMMAND_CREATION_EXCEPTION(MESSAGE_IMPORT_INVALID_FILEPATH);
	}
	_filePath = filePath;
}

UIFeedback ImportCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	try {
		runTimeStorage -> loadFromFile(_filePath);
	} catch (INVALID_FILE_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	} catch (INVALID_PATH_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	}

	postExecutionAction(runTimeStorage);

	char buffer[255];
	sprintf_s(buffer, MESSAGE_IMPORT_SUCCESS.c_str(), _filePath.c_str());
	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), std::string(buffer));
}

UIFeedback ImportCommand::undo() {
	assert(false);
	return UIFeedback();
}

bool ImportCommand::canUndo() {
	return false;
}

ImportCommand::~ImportCommand(void){
}
