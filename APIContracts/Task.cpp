#include "Task.h"

#include <string>

	Task::Task(std::string taskText, boost::posix_time::ptime startDateTime, boost::posix_time::ptime endDateTime) {
		_taskText = taskText;
		_startDateTime = startDateTime;
		_endDateTime = endDateTime;
	}

	std::string Task::getTaskText() {
		return _taskText;
	}

	//int to be replace by dateTime object
	boost::posix_time::ptime Task::getStartDateTime() {
		return _startDateTime;
	}

	boost::posix_time::ptime Task::getEndDateTime() {
		return _endDateTime;
	}
