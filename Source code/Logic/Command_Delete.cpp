//@@author A0112218W

#include "Command_Delete.h"

DeleteCommand::DeleteCommand(CommandTokens::SecondaryCommandType type2) : Command(CommandTokens::PrimaryCommandType::Delete) {
	_type2 = type2;
}

bool DeleteCommand::canUndo() {
	return true;
}

DeleteIndexCommand::DeleteIndexCommand(size_t index) : DeleteCommand(CommandTokens::SecondaryCommandType::Index) {
	_index = index;
	_entryIndex = std::numeric_limits<size_t>::infinity();
}

UIFeedback DeleteIndexCommand::execute(RunTimeStorage* runTimeStorage) {
	assert (runTimeStorage != NULL);
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
			feedback = UIFeedback(runTimeStorage->refreshTasksToDisplay(),feedbackMessage);
			_statusExecuted = true;
			_runTimeStorageExecuted = runTimeStorage;
		} 
	} catch (INDEX_NOT_FOUND_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	}
	return feedback;
}

UIFeedback DeleteIndexCommand::undo() {
	assert(_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	_runTimeStorageExecuted -> insert(_taskDeleted, _entryIndex);
	_taskDeleted = Task();
	_entryIndex = std::numeric_limits<size_t>::infinity();
	return UIFeedback(_runTimeStorageExecuted->refreshTasksToDisplay(), MESSAGE_DELETE_UNDO);
}

DeleteIndexCommand::~DeleteIndexCommand() {
}

DeleteBeforeCommand::DeleteBeforeCommand(ptime endDateTime) : DeleteCommand(CommandTokens::SecondaryCommandType::By) {
	assert(!endDateTime.is_special());
	_endDateTime = endDateTime;
}

UIFeedback DeleteBeforeCommand::execute(RunTimeStorage* runTimeStorage) {
	assert (runTimeStorage != NULL);
	try {
		std::vector<Task> tasks = runTimeStorage ->getAllTasks();
		int numTask = tasks.size();
		for (int i = 0 ; i < numTask; ++i) {
			ptime time = tasks[i].getEndDateTime();
			if (!time.is_special()) {
				if (time < _endDateTime) {
					_tasksDeleted.push_back(tasks[i]);
					_indexTaskDeleted.push_back(i);
				}
			}
		}

		if (_tasksDeleted.empty()) {
			throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_DELETE_EMPTY);
		}

		numTask = _tasksDeleted.size();

		//backward delete so that index of tasks before it will not be affected.
		for (int i = numTask -1 ; i >= 0 ; --i) {
			runTimeStorage->removeEntry(_indexTaskDeleted[i]);
		}
	} catch (INDEX_NOT_FOUND_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	} catch (COMMAND_EXECUTION_EXCEPTION e) {
		throw e;
	}

	_runTimeStorageExecuted = runTimeStorage;
	_statusExecuted = true;
	std::string feedbackMessage;
	char buffer[255];
	sprintf_s(buffer,
		MESSAGE_DELETE_BEFORE_SUCCESS.c_str(),						
		boost::posix_time::to_simple_string(_endDateTime).c_str());
	feedbackMessage = std::string(buffer);
	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), feedbackMessage);
}

UIFeedback DeleteBeforeCommand::undo(void) {
	assert (_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	assert(!_tasksDeleted.empty());
	assert(_tasksDeleted.size() == _indexTaskDeleted.size());

	for (size_t i = 0 ; i < _tasksDeleted.size() ; ++i) {
		_runTimeStorageExecuted -> insert (_tasksDeleted[i], _indexTaskDeleted[i]);
	}

	_tasksDeleted.clear();
	_indexTaskDeleted.clear();

	return UIFeedback(_runTimeStorageExecuted -> refreshTasksToDisplay(), MESSAGE_DELETE_UNDO);
}

DeleteBeforeCommand::~DeleteBeforeCommand(void) {
}

DeleteFromToCommand::DeleteFromToCommand(ptime startDateTime, ptime endDateTime) : DeleteCommand(CommandTokens::SecondaryCommandType::FromTo){
	assert(!(startDateTime.is_special() || endDateTime.is_special()));
	if (endDateTime < startDateTime) {
		throw COMMAND_CREATION_EXCEPTION (MESSAGE_END_LESS_THAN_START);
	}
	_startDateTime = startDateTime;
	_endDateTime = endDateTime;
}

UIFeedback DeleteFromToCommand::execute(RunTimeStorage* runTimeStorage) {
	assert (runTimeStorage != NULL);
	try {
		std::vector<Task> tasks = runTimeStorage ->getAllTasks();
		int numTask = tasks.size();
		for (int i = 0 ; i < numTask; ++i) {
			ptime startDateTime = tasks[i].getStartDateTime();
			ptime endDateTime = tasks[i].getEndDateTime();
			if (!(startDateTime.is_special()||endDateTime.is_special())) {
				if (startDateTime > _startDateTime && endDateTime < _endDateTime) {
					_tasksDeleted.push_back(tasks[i]);
					_indexTaskDeleted.push_back(i);
				}
			}
		}

		if (_tasksDeleted.empty()) {
			throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_DELETE_EMPTY);
		}

		numTask = _tasksDeleted.size();

		//backward delete so that index of tasks before it will not be affected.
		for (int i = numTask -1 ; i >= 0 ; --i) {
			runTimeStorage->removeEntry(_indexTaskDeleted[i]);
		}
	} catch (INDEX_NOT_FOUND_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	} catch (COMMAND_EXECUTION_EXCEPTION e) {
		throw e;
	}

	_runTimeStorageExecuted = runTimeStorage;
	_statusExecuted = true;
	std::string feedbackMessage;
	char buffer[255];
	sprintf_s(buffer,
		MESSAGE_DELETE_FROMTO_SUCCESS.c_str(),
		boost::posix_time::to_simple_string(_startDateTime).c_str(),
		boost::posix_time::to_simple_string(_endDateTime).c_str());
	feedbackMessage = std::string(buffer);
	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), feedbackMessage);
}

UIFeedback DeleteFromToCommand::undo(void) {
	assert (_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	assert(!_tasksDeleted.empty());
	assert(_tasksDeleted.size() == _indexTaskDeleted.size());

	for (size_t i = 0 ; i < _tasksDeleted.size() ; ++i) {
		_runTimeStorageExecuted -> insert (_tasksDeleted[i], _indexTaskDeleted[i]);
	}

	_tasksDeleted.clear();
	_indexTaskDeleted.clear();

	return UIFeedback(_runTimeStorageExecuted -> refreshTasksToDisplay(), MESSAGE_DELETE_UNDO);
}

DeleteFromToCommand::~DeleteFromToCommand(void) {
}

DeleteAllCommand::DeleteAllCommand(void) : DeleteCommand(CommandTokens::SecondaryCommandType::All){
}

UIFeedback DeleteAllCommand::execute(RunTimeStorage* runTimeStorage) {
	assert (runTimeStorage != NULL);
	assert (_tasksDeleted.empty());
	UIFeedback feedback;
	try {
		_tasksDeleted = runTimeStorage->getAllTasks();
		runTimeStorage->removeAll();
		feedback = UIFeedback(runTimeStorage->refreshTasksToDisplay(), MESSAGE_DELETE_ALL_SUCCESS);
		_statusExecuted = true;
		_runTimeStorageExecuted = runTimeStorage;
	} catch (EMPTY_STORAGE_EXCEPTION e) {
		throw COMMAND_EXECUTION_EXCEPTION(e.what());
	}

	return feedback;
}

UIFeedback DeleteAllCommand::undo() {
	assert(_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	assert(!_tasksDeleted.empty());
	for (size_t i = 0 ; i < _tasksDeleted.size() ; ++i){
		_runTimeStorageExecuted -> add(_tasksDeleted[i]);
	}

	_tasksDeleted.clear();
	return UIFeedback(_runTimeStorageExecuted->refreshTasksToDisplay(), MESSAGE_DELETE_UNDO);
}

DeleteAllCommand::~DeleteAllCommand() {
}

DeleteCompleteCommand::DeleteCompleteCommand (void) : DeleteCommand(CommandTokens::Completed){
}

UIFeedback DeleteCompleteCommand::execute(RunTimeStorage* runTimeStorage) {
	assert (runTimeStorage != NULL);
	assert (_tasksDeleted.empty());
	UIFeedback feedback;
	try {
		std::vector<Task> tasks = runTimeStorage->getAllTasks();
		size_t numTask = tasks.size();
		for (size_t i = 0 ; i < numTask ; ++i) {
			if (tasks[i].isComplete()) {
				_tasksDeleted.push_back(tasks[i]);
				_indexTaskDeleted.push_back(i);
			}
		}

		if (_tasksDeleted.empty()) {
			throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_DELETE_EMPTY);
		}

		numTask = _tasksDeleted.size();

		//backward delete so that index of tasks before it will not be affected.
		for (int i = numTask -1 ; i >= 0 ; --i) {
			runTimeStorage->removeEntry(_indexTaskDeleted[i]);
		}		
	} catch (COMMAND_EXECUTION_EXCEPTION e) {
		throw e;
	}

	_statusExecuted = true;
	_runTimeStorageExecuted = runTimeStorage;

	char buffer[255];
	sprintf_s(buffer, MESSAGE_DELETE_COMPLETE_SUCCESS.c_str());

	return UIFeedback(runTimeStorage->refreshTasksToDisplay(), buffer);
}

UIFeedback DeleteCompleteCommand::undo(void) {
	assert (_statusExecuted);
	assert(_runTimeStorageExecuted!=NULL);
	assert(!_tasksDeleted.empty());
	assert(_tasksDeleted.size() == _indexTaskDeleted.size());

	for (size_t i = 0 ; i < _tasksDeleted.size() ; ++i) {
		_runTimeStorageExecuted -> insert (_tasksDeleted[i], _indexTaskDeleted[i]);
	}

	_tasksDeleted.clear();
	_indexTaskDeleted.clear();

	return UIFeedback(_runTimeStorageExecuted -> refreshTasksToDisplay(), MESSAGE_DELETE_UNDO);
}

DeleteCompleteCommand::~DeleteCompleteCommand(void) {
}