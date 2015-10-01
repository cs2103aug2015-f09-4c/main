#include "Command.h"

Command::Command(PrimaryCommandType type) {
	_type1 = type;
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

InvalidCommand::InvalidCommand() : Command(PrimaryCommandType::Invalid){
}

UIFeedback InvalidCommand::execute(StorageHandler* storageHandler) {
	UIFeedback feedback(storageHandler->getTasksToDisplay(), MESSAGE_INVALID);
	return feedback;
}

AddCommand::AddCommand (SecondaryCommandType type2, Task task) : Command(PrimaryCommandType::Add) {
	_type2 = type2;
	_task = task;
}

UIFeedback AddCommand::execute(StorageHandler* storageHandler) {
	UIFeedback* feedback;
	if (_task.getTaskText().size() < 1) {
		feedback = new UIFeedback(storageHandler->getTasksToDisplay(), MESSAGE_ADD_EMPTY);
	} else if (storageHandler->isDuplicate(_task)) {
		feedback = new UIFeedback(storageHandler->getTasksToDisplay(), MESSAGE_ADD_DUPLICATE);
	} else {
		storageHandler->add(_task);
		std::string taskText = _task.getTaskText();
		std::string startDateTime = boost::posix_time::to_simple_string(_task.getStartDateTime());
		std::string endDateTime = boost::posix_time::to_simple_string(_task.getEndDateTime());
		char buffer[255];
		sprintf_s(buffer, MESSAGE_ADD_SUCCESS.c_str(), taskText.c_str(), startDateTime.c_str(), endDateTime.c_str());
		std::string feedbackMessage(buffer);
		feedback = new UIFeedback(storageHandler->getTasksToDisplay(), feedbackMessage);
	}
	return *feedback;
}

bool AddCommand::isValid() {
	if (_type2 == SecondaryCommandType::None) {
		return false;
	} else {
		return Command::isValid();
	}
}

Task AddCommand::getTask() {
	return _task;
}

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
	_taskDeleted = storageHandler->remove(_index);
	UIFeedback *feedback = NULL;
	if (_taskDeleted.isValid()) {
		char buffer[255];
		sprintf_s(buffer,MESSAGE_DELETE_INDEX_SUCCESS.c_str(),_index);
		std::string feedbackMessage(buffer);
		feedback = new UIFeedback(storageHandler->getTasksToDisplay(),feedbackMessage);
	} else {
		char buffer[255];
		sprintf_s(buffer,MESSAGE_DELETE_INDEX_FAIL.c_str(),_index);
		std::string feedbackMessage(buffer);
		feedback = new UIFeedback(storageHandler->getTasksToDisplay(),feedbackMessage);
	}
	return *feedback;
}

InvalidDeleteCommand::InvalidDeleteCommand() : DeleteCommand(SecondaryCommandType::None) {
}

UIFeedback InvalidDeleteCommand::execute(StorageHandler* storageHandler) {
	UIFeedback feedback(storageHandler->getAllTasks(), MESSAGE_INVALID);
	return feedback;
}