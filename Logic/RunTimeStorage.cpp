//@@author A0112218W

#include "RunTimeStorage.h"

//Constructor
RunTimeStorage::RunTimeStorage(){
	//Default display and sort mode for initialization
	_displayMode = Display_Type::displayAll;
	_sortMode = Sort_Type::sortByEntryOrder;

	_physicalStorageHandler = new PhysicalStorageHandler();
	_physicalStorageHandler->loadFromFile(_tasks);
}

//Getter
std::vector<Task>& RunTimeStorage::getAllTasks() {
	return _tasks;
}

std::vector<Task>& RunTimeStorage::getTasksToDisplay() {
	return _tasksToDisplay;
}

std::vector<Task>& RunTimeStorage::refreshTasksToDisplay() {
	updateDisplay();
	return _tasksToDisplay;
}

void RunTimeStorage::setTasksToDisplay(std::vector<Task> tasks) {
	for (size_t i = 0 ; i < tasks.size() ; ++i) {
		assert(std::find(_tasks.begin(), _tasks.end(), tasks[i]) != _tasks.end());
	}

	_tasksToDisplay = tasks;
}

//return the task reference object in _tasks based on index of _tasksToDisplay
//index is provided by user, thus it is in base-1 (start from 1 instead of 0)
Task& RunTimeStorage::find(size_t index) {
	if (index > _tasksToDisplay.size()) {
		throw INDEX_NOT_FOUND_EXCEPTION(index);
	}

	Task taskToReturn = _tasksToDisplay[index-1];
	std::vector<Task>::iterator iter = std::find(_tasks.begin(), _tasks.end(), taskToReturn);

	return *iter;
}

//find index of task in _tasks
//used for undo purpose whereby editing task on exact index is needed
//return index is in base-0
size_t RunTimeStorage::find(Task& task) {
	for (size_t i = 0 ; i < _tasks.size() ; ++i) {
		if (_tasks[i] == task) {
			return i;
		}
	}

	//if not found, return an invalid index
	return _tasks.size();
}

//return task reference object in _tasks based on index of _tasks
//index is base-0
Task& RunTimeStorage::getEntry(size_t index) {
	if (index >= _tasks.size()) {
		throw INDEX_NOT_FOUND_EXCEPTION(index);
	}

	return _tasks[index];
}

//add a task to runTimeStorage
//no duplicate task is allowed.
void RunTimeStorage::add(Task task) {
	if (isDuplicate(task)) {
		throw DUPLICATE_TASK_EXCEPTION(); 
	}
	_tasks.push_back(task);
	return;
}

//add a task into specified index in _tasks
//used for undo only as _entryOrder need to be maintained
void RunTimeStorage::insert(Task task, size_t index) {
	assert(!isDuplicate(task));
	_tasks.insert(_tasks.begin()+index, task);
	return;
}

void RunTimeStorage::removeLastEntry() {
	_tasks.pop_back();
	return;
}

bool RunTimeStorage::isDuplicate(Task task) {
	size_t n = _tasks.size();
	for (size_t i = 0 ; i < n ; ++i) {
		if (_tasks[i] == task) {
			return true;
		}
	}
	return false;
}

Task RunTimeStorage::remove(size_t index) {
	if (index > _tasksToDisplay.size()) {
		throw INDEX_NOT_FOUND_EXCEPTION(index);
	}

	Task taskToDelete = _tasksToDisplay[index-1];

	std::vector<Task>::iterator iter = std::find(_tasks.begin(),_tasks.end(), taskToDelete);

	_tasksToDisplay.erase(_tasksToDisplay.begin() + index - 1);
	_tasks.erase(iter);

	return taskToDelete;
}

void RunTimeStorage::removeEntry(size_t index) {
	if (index > _tasks.size()) {
		throw INDEX_NOT_FOUND_EXCEPTION(index);
	}

	_tasks.erase(_tasks.begin() + index);
}

void RunTimeStorage::removeAll(void) {
	if (_tasks.empty()) {
		throw EMPTY_STORAGE_EXCEPTION();
	}

	_tasks.clear();

	return;
}

Display_Type RunTimeStorage::getDisplayType() {
	return _displayMode;
}

void RunTimeStorage::changeDisplayType(Display_Type type) {
	_displayMode = type;
}

Sort_Type RunTimeStorage::getSortType() {
	return _sortMode;
}

void RunTimeStorage::changeSortType(Sort_Type type) {
	_sortMode = type;
}

bool RunTimeStorage::isValidForDisplay(Task task) {
	boost::posix_time::ptime startDateTime = task.getStartDateTime();
	boost::posix_time::ptime endDateTime = task.getEndDateTime();
	switch(_displayMode) {
	case Display_Type::displayFloat:
		return startDateTime.is_special() && endDateTime.is_special();
	case Display_Type::displayTimed:
		return !startDateTime.is_special() && !endDateTime.is_special();
	case Display_Type::displayTodo:
		return startDateTime.is_special() && !endDateTime.is_special();
	default:
		return true;
	}
}

bool RunTimeStorage::isValidIndex(size_t index) {
	if (index < _tasks.size()) {
		return true;
	} else {
		return false;
	}
}

void RunTimeStorage::reformTasksToDisplay() {
	_tasksToDisplay.clear();

	for (std::vector<Task>::iterator iter = _tasks.begin() ; iter != _tasks.end() ; ++iter) {
		if (isValidForDisplay(*iter)) {
			_tasksToDisplay.push_back(*iter);
		}
	}

	return;
}

//Pre-condition : TasksToDisplay is in sortByEntryOrder
//Post-condition: TasksToDisplay is sorted according to _sortMode
//              : The sort is stable
void RunTimeStorage::sortTasksToDisplay() {
	switch(_sortMode) {
	case Sort_Type::sortByEntryOrder:
		break;
	case Sort_Type::sortByName:
		std::stable_sort(_tasksToDisplay.begin(),_tasksToDisplay.end(),Task::sortByNameAscending);
		break;
	case Sort_Type::sortByStart:
		std::stable_sort(_tasksToDisplay.begin(),_tasksToDisplay.end(),Task::sortByStartDateTimeAscending);
		break;
	case Sort_Type::sortByEnd:
		std::stable_sort(_tasksToDisplay.begin(),_tasksToDisplay.end(),Task::sortByEndDateTimeAscending);
		break;
	case Sort_Type::sortByNameDesc:
		std::stable_sort(_tasksToDisplay.begin(),_tasksToDisplay.end(),Task::sortByNameDescending);
		break;
	case Sort_Type::sortByStartDesc:
		std::stable_sort(_tasksToDisplay.begin(),_tasksToDisplay.end(),Task::sortByStartDateTimeDescending);
		break;
	case Sort_Type::sortByEndDesc:
		std::stable_sort(_tasksToDisplay.begin(),_tasksToDisplay.end(),Task::sortByEndDateTimeDescending);
		break;
	}
	return;
}

void RunTimeStorage::updateDisplay() {
	reformTasksToDisplay();
	sortTasksToDisplay();
	return;
}

void RunTimeStorage::saveToFile() {
	_physicalStorageHandler->saveToFile(_tasks);
	return;
}

void RunTimeStorage::saveToFile(std::string filePath) {
	_physicalStorageHandler->saveToFile(_tasks, filePath);
	return;
}

void RunTimeStorage::loadFromFile() {
	_physicalStorageHandler->loadFromFile(_tasks);
	return;
}

void RunTimeStorage::loadFromFile(std::string filePath) {
	_physicalStorageHandler->loadFromFile(_tasks, filePath);
	return;
}