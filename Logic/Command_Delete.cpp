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

bool DeleteCommand::canUndo() {
	return true;
}

IndexDeleteCommand::IndexDeleteCommand(size_t index) : DeleteCommand(SecondaryCommandType::Index) {
	_index = index;
}

UIFeedback IndexDeleteCommand::execute(RunTimeStorage* runTimeStorage) {
	UIFeedback feedback;
	try {
		_taskDeleted = runTimeStorage->remove(_index);

		if (_taskDeleted.isValid()) {
		char buffer[255];
		sprintf_s(buffer,MESSAGE_DELETE_INDEX_SUCCESS.c_str(),_index);
		std::string feedbackMessage(buffer);
		feedback = UIFeedback(runTimeStorage->getTasksToDisplay(),feedbackMessage);
		_statusExecuted = true;
		} 
	} catch (INDEX_NOT_FOUND_EXCEPTION e) {
		feedback = UIFeedback(runTimeStorage->getTasksToDisplay(), e.what());
	}
	return feedback;
}

UIFeedback IndexDeleteCommand::undo() {
	//TODO
	return UIFeedback();
}

IndexDeleteCommand::~IndexDeleteCommand() {
}