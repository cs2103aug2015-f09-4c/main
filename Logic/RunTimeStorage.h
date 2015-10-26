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
	displayAll, displayFloat, displayTimed, displayTodo, displayStartBefore, displayStartAfter
};

enum Sort_Type {
	sortByEntryOrder, sortByName, sortByStart, sortByEnd
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
	
	//Time object used for comparison when selecting tasks to display for displayBefore and displayAfter
	ptime _time;

	//If the task fit _displayMode, return true, else return false
	bool isValidForDisplay(Task task);

	//comparator functions for sorting
	static bool sortByStartDateTime (Task task1, Task task2);
	static bool sortByEndDateTime (Task task1, Task task2);
	static bool sortByName (Task task1, Task task2);

	//Filter tasks from Tasks into TasksToDisplay based on _displayMode
	//Post-condition: Tasks in TasksToDisplay is sorted by entry order
	void reformTasksToDisplay();

	//Pre-condition : TasksToDisplay is in sortByEntryOrder
	//Post-condition: TasksToDisplay is sorted according to _sortMode
	//              : The sort is stable
	void sortTasksToDisplay();

	//update TasksToDisplay based on _displayMode and _sortMode
	void updateDisplay();

public:
	RunTimeStorage();

	std::vector<Task>& getAllTasks();
	std::vector<Task>& getTasksToDisplay();

	void add(Task task);
	void insert(Task task, size_t index);

	void removeLastEntry();
	Task remove(size_t index);
	void removeEntry(size_t index);
	void removeAll();	

	Task& find(size_t index);
	size_t find(Task& task);
	Task& getEntry(size_t index);

	bool isDuplicate(Task task);
	bool isValidIndex(size_t index);

	void setTimeForCompare(ptime time);
	void changeDisplayType(Display_Type type);
	void changeSortType(Sort_Type type);

	void saveToFile();
	void saveToFile(std::string filePath);
};