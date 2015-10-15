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

enum Display_Type {
	displayAll, displayFloat, displayTimed, displayTodo
};

enum Sort_Type {
	sortByEntryOrder, sortByName, sortByStart, sortByEnd
};

class INDEX_NOT_FOUND_EXCEPTION : public std::exception {
private:
	std::string _message;
public:
	explicit INDEX_NOT_FOUND_EXCEPTION (const int index) : std::exception() {
		_message = std::string("No task is found at index ") + std::to_string(index);
	}

	const char* what() const throw() {
		return _message.c_str();
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
	Task& find(size_t index);
	size_t find(Task& task);
	Task& getEntry(size_t index);

	bool isDuplicate(Task task);
	bool isValidIndex(size_t index);

	void changeDisplayType(Display_Type type);
	void changeSortType(Sort_Type type);

	void saveToFile();
	void saveToFile(std::string filePath);
};