#include "Command.h"

Command::Command(PrimaryCommandType type) {
	_type1 = type;
	_statusExecuted = false;
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

bool Command::isExecutedSuccessfully() {
	return _statusExecuted;
}

