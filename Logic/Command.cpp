#include <assert.h>
#include <limits>
#include "Command.h"

Command::Command(PrimaryCommandType type) {
	_type1 = type;
	_statusExecuted = false;
	_runTimeStorageExecuted = NULL;
}

PrimaryCommandType Command::getPrimaryCommandType() {
	return _type1;
}

SecondaryCommandType Command::getSecondaryCommandType() {
	return _type2;
}

bool Command::isValid() {
	if (_type1 == PrimaryCommandType::Invalid) {
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

