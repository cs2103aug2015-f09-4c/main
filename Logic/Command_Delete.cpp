#include "Command_Delete.h"

DeleteCommand::DeleteCommand(SecondaryCommandType type2) : Command(PrimaryCommandType::Delete) {
	_type2 = type2;
}

bool DeleteCommand::isValid() {
	if (_type2 == SecondaryCommandType::None) {
		return false;
	} else {
		return Command::isValid();
	}
}

IndexDeleteCommand::IndexDeleteCommand(size_t index) : DeleteCommand(SecondaryCommandType::Index) {
	_index = index;
}

UIFeedback IndexDeleteCommand::execute(StorageHandler* storageHandler) {
	UIFeedback feedback;
	try {
		_taskDeleted = storageHandler->remove(_index);

		if (_taskDeleted.isValid()) {
		char buffer[255];
		sprintf_s(buffer,MESSAGE_DELETE_INDEX_SUCCESS.c_str(),_index);
		std::string feedbackMessage(buffer);
		feedback = UIFeedback(storageHandler->getTasksToDisplay(),feedbackMessage);
		_statusExecuted = true;
		} 
	} catch (INDEX_NOT_FOUND_EXCEPTION e) {
		feedback = UIFeedback(storageHandler->getTasksToDisplay(), e.what());
	}
	return feedback;
}

IndexDeleteCommand::~IndexDeleteCommand() {
}