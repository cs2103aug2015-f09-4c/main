#pragma once

// TODO this include may not belong here, move it
#include <set>
#include "../boost/date_time/posix_time/posix_time.hpp"

const std::string MESSAGE_EMPTY_TASK_TEXT = "Task text cannot be empty.";
const std::string MESSAGE_END_LESS_THAN_START = "Start date time must be before end date time.";
const std::string MESSAGE_EMPTY_END_DATE = "When start date time is a defined date-time, end date time cannot be not a date time.";

class TASK_EXCEPTION : public std::exception {
public:
	explicit TASK_EXCEPTION(std::string message);
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
	Task(std::string taskText, boost::posix_time::ptime endDateTime);

	//Constructor for timed task
	Task(std::string taskText, boost::posix_time::ptime startDateTime, boost::posix_time::ptime endDateTime);

	//Getters
	std::string getTaskText();
	boost::posix_time::ptime getStartDateTime();
	boost::posix_time::ptime getEndDateTime();

	//Methods
	bool operator==(Task another);
	bool isValid();
	bool isComplete();

	//Modifiers
	void changeTaskText(std::string newTaskText);
	void changeStartDateTime(boost::posix_time::ptime newStartDateTime);
	void changeEndDateTime(boost::posix_time::ptime newEndDateTime);
	void toggleComplete();

private:
	std::string _taskText;
	boost::posix_time::ptime _startDateTime;
	boost::posix_time::ptime _endDateTime;
	bool _isComplete;
	std::set<std::string> _tags; 

	static bool isEndLessThanStart(boost::posix_time::ptime start, boost::posix_time::ptime end);
};
}
