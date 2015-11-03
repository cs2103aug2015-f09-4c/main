//@@author A0112218W

#pragma once

// TODO this include may not belong here, move it
#include <set>
#include "../boost/date_time/posix_time/posix_time.hpp"

typedef class boost::posix_time::ptime ptime;

const std::string MESSAGE_EMPTY_TASK_TEXT = "Task text cannot be empty.";
const std::string MESSAGE_LONG_TASK_TEXT = "Task text cannot be more than 128 characters long.";
const std::string MESSAGE_INVALID_FIRST_CHARACTER = "First character of task text has to be alphanumeric.";
const std::string MESSAGE_END_LESS_THAN_START = "Start date time must be before end date time.";
const std::string MESSAGE_EMPTY_END_DATE = "When start date time is a defined date-time, end date time cannot be not a date time.";
const std::string MESSAGE_DUPLICATE_TAG = "%s already exist, tag cannot be added.";
const std::string MESSAGE_TAG_NOT_FOUND = "%s not found, tag cannot be removed.";
const std::string MESSAGE_TAG_LIMIT_REACHED = "Maximum no. of tag has been reached, no more tag can be added.";
const std::string MESSAGE_LONG_TAG = "Length of tag cannot be more than 32 (Including #).";
const std::string MESSAGE_TAG_FIRST_CHARACTER_NOT_HASH = "First character of tag must be \'#\'";

const int MAX_TASK_NAME_LENGTH = 128;
const int MAX_TAG_LENGTH = 32;
const int MAX_TAG_NUM = 5;

class TASK_EXCEPTION : public std::exception {
public:
	explicit TASK_EXCEPTION(std::string message);
};

class TAG_LIMIT_EXCEPTION : public TASK_EXCEPTION {
public:
	explicit TAG_LIMIT_EXCEPTION();
};

namespace API{
class Task
{
public:
	//Constructor for invalid task
	Task();

	//Constructor for floating task
	Task(std::string taskText);

	//Constructor for toDo task
	Task(std::string taskText, ptime endDateTime);

	//Constructor for timed task
	Task(std::string taskText, ptime startDateTime, ptime endDateTime);

	//Getters
	std::string getTaskText();
	ptime getStartDateTime();
	ptime getEndDateTime();
	std::set<std::string>& getTags();

	//Methods
	bool operator==(Task another);
	bool isValid();
	bool isComplete();

	//Modifiers
	void changeTaskText(std::string newTaskText);
	void changeStartDateTime(ptime newStartDateTime);
	void changeEndDateTime(ptime newEndDateTime);
	void toggleComplete();
	void addTag(std::string);
	void removeTag(std::string);

	//comparator functions for sorting
	static bool sortByStartDateTimeAscending (Task task1, Task task2);
	static bool sortByEndDateTimeAscending (Task task1, Task task2);
	static bool sortByNameAscending (Task task1, Task task2);
	static bool sortByStartDateTimeDescending (Task task1, Task task2);
	static bool sortByEndDateTimeDescending (Task task1, Task task2);
	static bool sortByNameDescending(Task task1, Task task2);

private:
	std::string _taskText;
	ptime _startDateTime;
	ptime _endDateTime;
	bool _isComplete;
	std::set<std::string> _tags; 

	static bool isEndLessThanStart(ptime start, ptime end);
	static bool isValidName(std::string name);
};
}