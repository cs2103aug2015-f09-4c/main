#pragma once

#include <fstream>
#include <algorithm>
#include "Task.h"
#include "UIFeedback.h"
#include "..\Parser\Parser.h"

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
	//Tasks is always sorted by Entry Order, the order of task being added
	std::vector<Task> _tasks;
	//TasksToDisplay is filtered out from Tasks and sorted based on _displayMode and _sortMode
	std::vector<Task> _tasksToDisplay;
	//_fileName/Path for saving
	std::string _fileName;
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
	RunTimeStorage(std::string fileName);

	std::vector<Task>& getAllTasks();
	std::vector<Task>& getTasksToDisplay();

	void add(Task task);
	Task remove(size_t index);
	Task& find(size_t index);

	bool isDuplicate(Task task);

	void changeDisplayType(Display_Type type);
	void changeSortType(Sort_Type type);

	void saveToFile ();
	void loadFromFile ();
};