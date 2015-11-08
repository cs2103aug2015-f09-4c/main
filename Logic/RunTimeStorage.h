//@@author A0112218W

#pragma once

#include <fstream>
#include <limits>
#include <algorithm>
#include "Task.h"
#include "UIFeedback.h"
#include "..\Parser\Parser.h"
#include "..\Storage\PhysicalStorageHandler.h"
#include "..\Logger\Logger.h"

using namespace API;

const std::string MESSAGE_DUPLICATE_TASK = "Duplicate task is found. No change is made.";
const std::string MESSAGE_EMPTY_STORAGE = "Storage is already empty. There is no task to delete.";
const std::string MESSAGE_INDEX_NOT_FOUND = "No task is found at index ";


enum Display_Type {
	displayAll,			//Display all tasks without filter
	displayFloat,		//Display only floating task
	displayTimed,		//Display only timed task
	displayTodo		//Display only todo task
};

enum Sort_Type {
	sortByEntryOrder,	//Sort tasks by entry order
	sortByName,			//Sort tasks by name in ascending order
	sortByStart,		//Sort tasks by start date time in ascending order
	sortByEnd,			//Sort tasks by end date time in ascending order
	sortByNameDesc,		//Sort tasks by name in descending order
	sortByStartDesc,	//Sort tasks by start date time in descending order
	sortByEndDesc		//Sort tasks by end date time in descending order
};

class INDEX_NOT_FOUND_EXCEPTION : public std::exception {
public:
	explicit INDEX_NOT_FOUND_EXCEPTION (const int index) : std::exception((MESSAGE_INDEX_NOT_FOUND + std::to_string(index)).c_str()) {
	}
};

class EMPTY_STORAGE_EXCEPTION : public std::exception {
public:
	explicit EMPTY_STORAGE_EXCEPTION () : std::exception(MESSAGE_EMPTY_STORAGE.c_str()) {
	}
};

class DUPLICATE_TASK_EXCEPTION : public std::exception {
public:
	explicit DUPLICATE_TASK_EXCEPTION() : std::exception(MESSAGE_DUPLICATE_TASK.c_str()) {
	}
};

class RunTimeStorage {
private:
	//_tasks is always sorted by Entry Order, the order of task being added
	std::vector<Task> _tasks;
	//_tasksToDisplay is filtered out from Tasks and sorted based on _displayMode and _sortMode
	std::vector<Task> _tasksToDisplay;

	PhysicalStorageHandler* _physicalStorageHandler;

	Display_Type _displayMode;
	Sort_Type _sortMode;

	//If the task fit _displayMode, return true, else return false
	bool isValidForDisplay(Task task);

	//Filter tasks from _tasks into _tasksToDisplay based on _displayMode
	void reformTasksToDisplay();

	//Sort _tasksToDisplay based on _sortMode
	void sortTasksToDisplay();

	//update TasksToDisplay based on _displayMode and _sortMode
	void updateDisplay();

public:
	RunTimeStorage();
	//return _tasks vector
	std::vector<Task>& getAllTasks();

	//return _tasksToDisplay vector
	std::vector<Task>& getTasksToDisplay();

	//update _tasksToDisplay and return the vector
	std::vector<Task>& refreshTasksToDisplay();

	//overwrite _tasksToDisplay with provided Task vector
	void setTasksToDisplay(std::vector<Task>);

	//add a task to _tasks vector at the end
	void add(Task task);

	//add a task to _tasks vector at index position provided.
	//If index is invalid, throw INDEX_NOT_FOUND_EXCEPTION
	void insert(Task task, size_t index);

	//remove task at the last position of _tasks
	void removeLastEntry();

	//remove task at the index position provided.
	//If index is invalid, throw INDEX_NOT_FOUND_EXCEPTION
	Task remove(size_t index);

	//remove task at the index position provided.
	//If index is invalid, throw INDEX_NOT_FOUND_EXCEPTION
	void removeEntry(size_t index);

	//remove all tasks in _tasks
	void removeAll();	

	//return the task in _tasksToDisplay based on index provided(1-based)
	//If index is invalid, throw INDEX_NOT_FOUND_EXCEPTION
	Task& find(size_t index);

	//return the index of task in _tasks (0-based)
	//if task is not found, return an invalid index which is size of _tasks
	size_t find(Task& task);

	//return the task in _tasks based on index provided (0-based)
	Task& getEntry(size_t index);

	//Check whether a duplicate task exist in _tasks
	bool isDuplicate(Task task);

	//Check whether an index is valid for _tasks or not
	bool isValidIndex(size_t index);

	Display_Type getDisplayType();
	void changeDisplayType(Display_Type type);
	Sort_Type getSortType();
	void changeSortType(Sort_Type type);

	void saveToFile();
	void saveToFile(std::string filePath);
	void loadFromFile();
	void loadFromFile(std::string filePath);
	void configureSaveLocation(std::string filePath);
	std::string getFilePath();
};