#include <assert.h>
#include <limits>
#include "Command.h"

COMMAND_EXECUTION_EXCEPTION::COMMAND_EXECUTION_EXCEPTION(const char* e) : std::exception(e) {
}

COMMAND_EXECUTION_EXCEPTION::COMMAND_EXECUTION_EXCEPTION(std::string errorMessage) : std::exception(errorMessage.c_str()) {
}

Command::Command(CommandTokens::PrimaryCommandType type) {
	_type1 = type;
	_statusExecuted = false;
	_runTimeStorageExecuted = NULL;
}

CommandTokens::PrimaryCommandType Command::getPrimaryCommandType() {
	return _type1;
}

CommandTokens::SecondaryCommandType Command::getSecondaryCommandType() {
	return _type2;
}

bool Command::isValid() {
	if (_type1 == CommandTokens::PrimaryCommandType::Invalid) {
		return false;
	} else {
		return true;
	}
}

bool Command::isExecuted() {
	return _statusExecuted;
}

RunTimeStorage* Command::getRunTimeStorageExecuted() {
	return _runTimeStorageExecuted;
}

