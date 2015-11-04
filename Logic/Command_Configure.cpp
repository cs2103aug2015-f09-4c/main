#include "Command_Configure.h"

ConfigureSaveLocationCommand::ConfigureSaveLocationCommand(std::string savePath) : Command(CommandTokens::PrimaryCommandType::Configure) {
	_newSavePath = savePath;
}

UIFeedback ConfigureSaveLocationCommand::execute(RunTimeStorage* runTimeStorage) {
	assert(runTimeStorage!=NULL);
	assert(!_statusExecuted);
	
	_oldSavePath = runTimeStorage->getFilePath();

	try {
		runTimeStorage->configureSaveLocation(_newSavePath);
	} catch (INVALID_PATH_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	} catch (INVALID_FILE_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	}

	_statusExecuted = true;
	_runTimeStorageExecuted = runTimeStorage;

	char buffer[255];
	sprintf_s(buffer, MESSAGE_CONFIG_SAVE_PATH_SUCCESS.c_str(), _newSavePath.c_str());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), buffer);
}

UIFeedback ConfigureSaveLocationCommand::undo() {
	assert(_runTimeStorageExecuted!=NULL);
	assert(_statusExecuted);

	_runTimeStorageExecuted->configureSaveLocation(_oldSavePath);

	std::vector<Task> tasksToDisplay = _runTimeStorageExecuted->getTasksToDisplay(); 

	_runTimeStorageExecuted = NULL;
	_statusExecuted = false;

	return UIFeedback(tasksToDisplay, MESSAGE_CONFIG_SAVE_PATH_UNDO);
}

bool ConfigureSaveLocationCommand::canUndo() {
	return true;
}

ConfigureSaveLocationCommand::~ConfigureSaveLocationCommand(void)
{
}
