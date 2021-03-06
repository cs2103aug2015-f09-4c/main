//@@author A0112218W

#include "Command_Search.h"

bool compareCount(const std::pair<int, Task>&i, const std::pair<int, Task>&j) {
	return i.first > j.first;
}

SearchCommand::SearchCommand(void) : Command(CommandTokens::Search) {
}

UIFeedback SearchCommand::undo() {
	assert(false);
	return UIFeedback();
}

bool SearchCommand::canUndo() {
	return false;
}

SearchCommand::~SearchCommand(void) {
}

SearchStartCommand::SearchStartCommand(ptime start) : SearchCommand() {
	assert(!start.is_special());
	_start = start;
}

SearchStartCommand::~SearchStartCommand(void) {
}

SearchStartBeforeCommand::SearchStartBeforeCommand(ptime start) : SearchStartCommand(start) {
	_type2 = CommandTokens::SecondaryCommandType::StartBefore;
}

UIFeedback SearchStartBeforeCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	_searchResult.clear();
	std::vector<Task>& tasks = runTimeStorage -> getAllTasks();

	for (size_t i = 0 ; i < tasks.size() ; ++i) {
		ptime start = tasks[i].getStartDateTime();
		if (!start.is_special()) {
			if (start < _start) {
				_searchResult.push_back(tasks[i]);
			}
		}
	}

	if (_searchResult.empty()) {
		throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_NO_TASK_FOUND);
	}

	std::stable_sort(_searchResult.begin(), _searchResult.end(), Task::sortByStartDateTimeAscending);
	runTimeStorage -> setTasksToDisplay(_searchResult);

	postExecutionAction(runTimeStorage);

	char buffer[255];
	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), _searchResult.size());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), std::string(buffer));
}

SearchStartBeforeCommand::~SearchStartBeforeCommand(void) {
}

SearchStartAfterCommand::SearchStartAfterCommand(ptime start) : SearchStartCommand(start) {
	_type2 = CommandTokens::SecondaryCommandType::StartAfter;
}

UIFeedback SearchStartAfterCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	_searchResult.clear();
	std::vector<Task>& tasks = runTimeStorage -> getAllTasks();

	for (size_t i = 0 ; i < tasks.size() ; ++i) {
		ptime start = tasks[i].getStartDateTime();
		if (!start.is_special()) {
			if (start > _start) {
				_searchResult.push_back(tasks[i]);
			}
		}
	}

	if (_searchResult.empty()) {
		throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_NO_TASK_FOUND);
	}

	std::stable_sort(_searchResult.begin(), _searchResult.end(), Task::sortByStartDateTimeAscending);
	runTimeStorage -> setTasksToDisplay(_searchResult);

	postExecutionAction(runTimeStorage);

	char buffer[255];
	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), _searchResult.size());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), std::string(buffer));
}

SearchStartAfterCommand::~SearchStartAfterCommand(void) {
}

SearchEndCommand::SearchEndCommand(ptime end) : SearchCommand() {
	assert(!end.is_special());
	_end = end;
}

SearchEndCommand::~SearchEndCommand(void) {
}

SearchEndBeforeCommand::SearchEndBeforeCommand(ptime end) : SearchEndCommand(end) {
	_type2 = CommandTokens::SecondaryCommandType::EndBefore;
}

UIFeedback SearchEndBeforeCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	_searchResult.clear();
	std::vector<Task>& tasks = runTimeStorage -> getAllTasks();

	for (size_t i = 0 ; i < tasks.size() ; ++i) {
		ptime end = tasks[i].getEndDateTime();
		if (!end.is_special()) {
			if (end < _end) {
				_searchResult.push_back(tasks[i]);
			}
		}
	}

	if (_searchResult.empty()) {
		throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_NO_TASK_FOUND);
	}

	std::stable_sort(_searchResult.begin(), _searchResult.end(), Task::sortByEndDateTimeAscending);
	runTimeStorage -> setTasksToDisplay(_searchResult);

	postExecutionAction(runTimeStorage);

	char buffer[255];
	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), _searchResult.size());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), std::string(buffer));
}

SearchEndBeforeCommand::~SearchEndBeforeCommand(void) {
}

SearchEndAfterCommand::SearchEndAfterCommand(ptime end) : SearchEndCommand(end) {
	_type2 = CommandTokens::SecondaryCommandType::EndAfter;
}

UIFeedback SearchEndAfterCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	_searchResult.clear();
	std::vector<Task>& tasks = runTimeStorage -> getAllTasks();

	for (size_t i = 0 ; i < tasks.size() ; ++i) {
		ptime end = tasks[i].getEndDateTime();
		if (!end.is_special()) {
			if (end > _end) {
				_searchResult.push_back(tasks[i]);
			}
		}
	}

	if (_searchResult.empty()) {
		throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_NO_TASK_FOUND);
	}

	std::stable_sort(_searchResult.begin(), _searchResult.end(), Task::sortByEndDateTimeAscending);
	runTimeStorage -> setTasksToDisplay(_searchResult);

	postExecutionAction(runTimeStorage);

	char buffer[255];
	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), _searchResult.size());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), std::string(buffer));
}

SearchEndAfterCommand::~SearchEndAfterCommand(void) {
}

SearchTagsCommand::SearchTagsCommand(std::vector<std::string> tags) : SearchCommand() {
	for (size_t i = 0 ; i < tags.size() ; ++i) {
		_tags.insert(tags[i]);
	}
	_type2 = CommandTokens::SecondaryCommandType::Tags;
}

UIFeedback SearchTagsCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	std::set<std::string>::iterator iter;
	std::vector<Task>& tasks = runTimeStorage->getAllTasks();
	size_t numTask = tasks.size();
	std::pair<int,Task>* taskCounter = new std::pair<int,Task> [numTask];

	for (size_t i = 0 ; i < numTask ; ++i) {
		taskCounter[i] = std::make_pair(0, tasks[i]);
	}

	for (iter = _tags.begin() ; iter != _tags.end() ; ++iter) {
		for (size_t i = 0 ; i < numTask ; ++i) {
			if (tasks[i].getTags().find(*iter) != tasks[i].getTags().end()) {
				taskCounter[i].first++;
			}
		}
	}

	std::stable_sort(taskCounter, taskCounter + numTask, compareCount);

	for (size_t i = 0 ; i < numTask ; ++i) {
		if (taskCounter[i].first == 0) {
			break;
		} else {
			_searchResult.push_back(taskCounter[i].second);
		}
	}

	runTimeStorage->setTasksToDisplay(_searchResult);
	delete[] taskCounter;

	postExecutionAction(runTimeStorage);

	char buffer[255];
	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), _searchResult.size());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), buffer);
}

SearchTagsCommand::~SearchTagsCommand(void) {
}

SearchNameCommand::SearchNameCommand(std::string searchString) {
	_searchString = searchString;
}

UIFeedback SearchNameCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);
	std::vector<Task>& tasks = runTimeStorage->getAllTasks();
	size_t numTask = tasks.size();

	std::smatch m;

	char buffer[255];
	sprintf_s(buffer,SEARCH_FORMAT_STRING.c_str(),_searchString.c_str());
	std::regex e(buffer, std::regex_constants::ECMAScript | std::regex_constants::icase);

	for (size_t i = 0 ; i < numTask ; ++i) {
		if (std::regex_search(tasks[i].getTaskText(),m,e)) {
			_searchResult.push_back(tasks[i]);
		}
	}

	if (_searchResult.empty()) {
		throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_NO_TASK_FOUND);
	}

	runTimeStorage -> setTasksToDisplay(_searchResult);

	postExecutionAction(runTimeStorage);

	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), _searchResult.size());

	return UIFeedback(runTimeStorage->getTasksToDisplay(), std::string(buffer));
}

SearchNameCommand::~SearchNameCommand() {
}

SearchFromToCommand::SearchFromToCommand(ptime start, ptime end) {
	_startDateTime = start;
	_endDateTime = end;
}

UIFeedback SearchFromToCommand::execute(RunTimeStorage* runTimeStorage) {
	checkIsValidForExecute(runTimeStorage);

	std::vector<Task>& tasks = runTimeStorage->getAllTasks();

	size_t numTask = tasks.size();

	for (size_t i = 0 ; i < numTask ; ++i) {
		ptime start = tasks[i].getStartDateTime();
		ptime end = tasks[i].getEndDateTime();
		if (!start.is_special() && !end.is_special()) {
			if (start >= _startDateTime && end <= _endDateTime) {
				_searchResult.push_back(tasks[i]);
			}
		}
	}

	if (_searchResult.empty()) {
		throw COMMAND_EXECUTION_EXCEPTION(MESSAGE_NO_TASK_FOUND);
	}

	runTimeStorage->setTasksToDisplay(_searchResult);

	postExecutionAction(runTimeStorage);

	char buffer[255];
	sprintf_s(buffer, MESSAGE_SEARCH_SUCCESS.c_str(), _searchResult.size());
	return UIFeedback(runTimeStorage->getTasksToDisplay(), buffer);
}

SearchFromToCommand::~SearchFromToCommand(void) {
}