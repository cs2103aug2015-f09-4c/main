#include "StorageHandler.h"

StorageHandler::StorageHandler(std::string fileName){
	_fileName = fileName;
	//Default display and sort mode for initialization
	_displayMode = Display_Type::displayAll;
	_sortMode = Sort_Type::sortByEntryOrder;
	//to be included after we finalized save file format
	//loadFromSaveFile(_fileName);
}

std::vector<Task>& StorageHandler::getAllTasks() {
	return Tasks;
}

std::vector<Task>& StorageHandler::getTasksToDisplay() {
	return TasksToDisplay;
}

void StorageHandler::add(Task task) {
	Tasks.push_back(task);
	updateDisplay();
	return;
}

bool StorageHandler::isDuplicate(Task task) {
	size_t n = Tasks.size();
	for (size_t i = 0 ; i < n ; ++i) {
		if (Tasks[i] == task) {
			return true;
		}
	}
	return false;
}

Task StorageHandler::remove(size_t index) {
	if (index > TasksToDisplay.size()) {
		return Task();		
	}

	Task taskToDelete = TasksToDisplay[index];

	std::vector<Task>::iterator iter = std::find(Tasks.begin(),Tasks.end(), taskToDelete);

	TasksToDisplay.erase(TasksToDisplay.begin() + index - 1);
	Tasks.erase(iter);

	return taskToDelete;
}

std::vector<Task> StorageHandler::changeDisplay(Display_Type type) {
	//to do
	return Tasks;
}	

//save and load are to be supported after we determine the save file format
//below are template assuming save file is in txt format.
/*
void loadFromSaveFile(std::string fileName) {
saveToSaveFile(_fileName);
Tasks.clear();
std::ifstream loadFile(fileName);
if (loadFile.is_open()) {
while (!loadFile.eof())
{
std::string taskText;
std::string startDateTimeString;
std::string endDateTimeString;

std::getline(loadFile,taskText);

std::getline(loadFile,startDateTimeString);
boost::posix_time::ptime startDateTime = boost::posix_time::time_from_string(startDateTimeString);

std::getline(loadFile,endDateTimeString);
boost::posix_time::ptime endDateTime = boost::posix_time::time_from_string(endDateTimeString);

Tasks.push_back(Task(taskText, startDateTime, endDateTime));
}
}
}
*/

/*
void saveToSaveFile(std::string fileName) {
std::ofstream saveFile(fileName);
for (size_t i = 0 ; i < Tasks.size() ; ++i) {
saveFile << Tasks[i].getTaskText() << "\n";
saveFile << boost::posix_time::to_simple_string(Tasks[i].getStartDateTime()) << "\n";
saveFile << boost::posix_time::to_simple_string(Tasks[i].getEndDateTime()) << "\n";
}
return;
}
*/

bool StorageHandler::isValidForDisplay(Task task) {
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

bool StorageHandler::sortByStartDateTime (Task task1, Task task2) {
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

bool StorageHandler::sortByEndDateTime (Task task1, Task task2) {
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


bool StorageHandler::sortByName (Task task1, Task task2) {
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

void StorageHandler::reformTasksToDisplay() {
	TasksToDisplay.clear();

	for (std::vector<Task>::iterator iter = Tasks.begin() ; iter != Tasks.end() ; ++iter) {
		if (isValidForDisplay(*iter)) {
			TasksToDisplay.push_back(*iter);
		}
	}

	return;
}

//Pre-condition : TasksToDisplay is in sortByEntryOrder
//Post-condition: TasksToDisplay is sorted according to _sortMode
//              : The sort is stable
void StorageHandler::sortTasksToDisplay() {
	switch(_sortMode) {
	case Sort_Type::sortByEntryOrder:
		break;
	case Sort_Type::sortByName:
		std::stable_sort(TasksToDisplay.begin(),TasksToDisplay.end(),sortByName);
		break;
	case Sort_Type::sortByStart:
		std::stable_sort(TasksToDisplay.begin(),TasksToDisplay.end(),sortByStartDateTime);
		break;
	case Sort_Type::sortByEnd:
		std::stable_sort(TasksToDisplay.begin(),TasksToDisplay.end(),sortByEndDateTime);
		break;
	}
	return;
}

void StorageHandler::updateDisplay() {
	reformTasksToDisplay();
	sortTasksToDisplay();
	return;
}