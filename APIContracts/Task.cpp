#include "Task.h"

#include <string>

	Task::Task(std::string taskText, int startDateTime, int endDateTime) {
		_taskText = taskText;
		_startDateTime = startDateTime;
		_endDateTime = endDateTime;
	}

	std::string Task::getTaskText() {
		return _taskText;
	}

	//int to be replace by dateTime object
	int Task::getStartDateTime() {
		return _startDateTime;
	}

	int Task::getEndDateTime() {
		return _endDateTime;
	}
