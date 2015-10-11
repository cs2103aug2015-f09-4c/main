#include "RunTimeStorage.h"

RunTimeStorage::RunTimeStorage(std::string fileName){
	_fileName = fileName;
	//Default display and sort mode for initialization
	_displayMode = Display_Type::displayAll;
	_sortMode = Sort_Type::sortByEntryOrder;
	//to be included after we finalized save file format
	loadFromFile();
}

std::vector<Task>& RunTimeStorage::getAllTasks() {
	return _tasks;
}

std::vector<Task>& RunTimeStorage::getTasksToDisplay() {
	updateDisplay();
	return _tasksToDisplay;
}

void RunTimeStorage::add(Task task) {
	_tasks.push_back(task);
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

Task& RunTimeStorage::find(size_t index) {
	if (index > _tasksToDisplay.size()) {
		throw INDEX_NOT_FOUND_EXCEPTION(index);
	}

	Task taskToReturn = _tasksToDisplay[index-1];
	std::vector<Task>::iterator iter = std::find(_tasks.begin(), _tasks.end(), taskToReturn);

	return *iter;
}

void RunTimeStorage::changeDisplayType(Display_Type type) {
	_displayMode = type;
}

void RunTimeStorage::changeSortType(Sort_Type type) {
	_sortMode = type;
}

void RunTimeStorage::loadFromFile() {
	_tasks.clear();
	std::ifstream loadFile(_fileName);
	if (loadFile.is_open()) {
		
		while (!loadFile.eof())
		{
			std::string taskText;
			std::string startDateTimeString;
			std::string endDateTimeString;
			std::string isCompleteString;

			std::getline(loadFile,taskText);
			if (taskText.empty()) {
				break;
			}

			std::getline(loadFile,startDateTimeString);
			boost::posix_time::ptime startDateTime;
			if (startDateTimeString != "not-a-date-time") {
				startDateTime = boost::posix_time::time_from_string(startDateTimeString);
			}

			std::getline(loadFile,endDateTimeString);
			boost::posix_time::ptime endDateTime;
			if (endDateTimeString != "not-a-date-time") {
				endDateTime = boost::posix_time::time_from_string(endDateTimeString);
			}

			std::getline(loadFile, isCompleteString);

			Task taskToAdd(taskText, startDateTime, endDateTime);
			if (isCompleteString == "1") {
				taskToAdd.setComplete();
			}

			_tasks.push_back(taskToAdd);
		}
	}
}



void RunTimeStorage::saveToFile() {
	std::ofstream saveFile(_fileName);
	for (size_t i = 0 ; i < _tasks.size() ; ++i) {
		saveFile << _tasks[i].getTaskText() << "\n";
		saveFile << boost::posix_time::to_simple_string(_tasks[i].getStartDateTime()) << "\n";
		saveFile << boost::posix_time::to_simple_string(_tasks[i].getEndDateTime()) << "\n";
		if (_tasks[i].isComplete()) {
			saveFile << "1\n";
		} else {
			saveFile << "0\n";
		}
	}
	return;
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

bool RunTimeStorage::sortByStartDateTime (Task task1, Task task2) {
	boost::posix_time::ptime startDateTime1 = task1.getStartDateTime();
	boost::posix_time::ptime startDateTime2 = task2.getStartDateTime();

	if (startDateTime2.is_special()) {
		return false;
	} else if (startDateTime1.is_special()) {
		return true;
	}

	if (startDateTime1 < startDateTime2) {
		return true;
	} else {
		return false;
	}
}

bool RunTimeStorage::sortByEndDateTime (Task task1, Task task2) {
	boost::posix_time::ptime endDateTime1 = task1.getStartDateTime();
	boost::posix_time::ptime endDateTime2 = task2.getStartDateTime();

	if (endDateTime2.is_special()) {
		return false;
	} else if (endDateTime1.is_special()) {
		return true;
	}

	if (endDateTime1 < endDateTime2) {
		return true;
	} else {
		return false;
	}
}


bool RunTimeStorage::sortByName (Task task1, Task task2) {
	std::string task1Text = task1.getTaskText();
	std::string task2Text = task2.getTaskText();

	size_t minStringLength = (std::min)(task1Text.size(), task2Text.size());


	for (size_t i = 0 ; i < minStringLength ; ++i) {
		task1Text[i] = std::tolower(task1Text[i]);
		task2Text[i] = std::tolower(task2Text[i]);
	}

	for (size_t i = 0 ; i < minStringLength ; ++i) {
		if (task1Text[i] < task2Text[i]) {
			return true;
		} else if (task1Text[i] > task2Text[i]) {
			return false;
		}
	}

	if (task1Text.size() < task2Text.size()) {
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
		std::stable_sort(_tasksToDisplay.begin(),_tasksToDisplay.end(),sortByName);
		break;
	case Sort_Type::sortByStart:
		std::stable_sort(_tasksToDisplay.begin(),_tasksToDisplay.end(),sortByStartDateTime);
		break;
	case Sort_Type::sortByEnd:
		std::stable_sort(_tasksToDisplay.begin(),_tasksToDisplay.end(),sortByEndDateTime);
		break;
	}
	return;
}

void RunTimeStorage::updateDisplay() {
	reformTasksToDisplay();
	sortTasksToDisplay();
	return;
}