#include "Command_Delete.h"

DeleteCommand::DeleteCommand(CommandTokens::SecondaryCommandType type2) : Command(CommandTokens::PrimaryCommandType::Delete) {
	_type2 = type2;
}

bool DeleteCommand::isValid() {
	if (_type2 == CommandTokens::SecondaryCommandType::None) {
		return false;
	} else {
		return Command::isValid();
	}
}

bool DeleteCommand::canUndo() {
	return true;
}

IndexDeleteCommand::IndexDeleteCommand(size_t index) : DeleteCommand(CommandTokens::SecondaryCommandType::Index) {
	_index = index;
	_entryIndex = std::numeric_limits<size_t>::infinity();
}

UIFeedback IndexDeleteCommand::execute(RunTimeStorage* runTimeStorage) {
	UIFeedback feedback;
	try {
		Task taskToDelete = runTimeStorage->find(_index);

		if (taskToDelete.isValid()) {
			_entryIndex = runTimeStorage->find(taskToDelete);
			assert(runTimeStorage->isValidIndex(_entryIndex));
			runTimeStorage->remove(_index);
			_taskDeleted = taskToDelete;
			char buffer[255];
			sprintf_s(buffer,MESSAGE_DELETE_INDEX_SUCCESS.c_str(),_index);
			std::string feedbackMessage(buffer);
			feedback = UIFeedback(runTimeStorage->getTasksToDisplay(),feedbackMessage);
			_statusExecuted = true;
			_runTimeStorageExecuted = runTimeStorage;
		} 
	} catch (INDEX_NOT_FOUND_EXCEPTION e) {
		feedback = UIFeedback(runTimeStorage->getTasksToDisplay(), e.what());
	}
	return feedback;
}

UIFeedback IndexDeleteCommand::undo() {
	assert(_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	_runTimeStorageExecuted -> insert(_taskDeleted, _entryIndex);
	_taskDeleted = Task();
	_entryIndex = std::numeric_limits<size_t>::infinity();
	return UIFeedback(_runTimeStorageExecuted->getTasksToDisplay(), MESSAGE_DELETE_UNDO);
}

IndexDeleteCommand::~IndexDeleteCommand() {
}

DeleteAllCommand::DeleteAllCommand(void) : DeleteCommand(CommandTokens::SecondaryCommandType::All){
}

UIFeedback DeleteAllCommand::execute(RunTimeStorage* runTimeStorage) {
	UIFeedback feedback;

	try {
		_tasksDeleted = runTimeStorage->getAllTasks();
		runTimeStorage->removeAll();
		feedback = UIFeedback(runTimeStorage->getTasksToDisplay(), MESSAGE_DELETE_ALL_SUCCESS);
		_statusExecuted = true;
		_runTimeStorageExecuted = runTimeStorage;
	} catch (std::exception e) {
		feedback = UIFeedback(runTimeStorage->getTasksToDisplay(), e.what());
	}

	return feedback;
}

UIFeedback DeleteAllCommand::undo() {
	assert(_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	assert(!_tasksDeleted.empty());
	for (int i = 0 ; i < _tasksDeleted.size() ; ++i){
		_runTimeStorageExecuted -> add(_tasksDeleted[i]);
	}

	_tasksDeleted.clear();
	return UIFeedback(_runTimeStorageExecuted->getTasksToDisplay(), MESSAGE_DELETE_UNDO);
}

DeleteAllCommand::~DeleteAllCommand() {
}
