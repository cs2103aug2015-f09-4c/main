#include "Task.h"
#include <string>
using namespace Swiftask;

	Task::Task() {
		_taskText = "";
	}

	Task::Task(std::string taskText) {
		_taskText = taskText;
	}

	Task::Task(std::string taskText, boost::posix_time::ptime endDateTime) {
		_taskText = taskText;
		_endDateTime = endDateTime;
	}

	Task::Task(std::string taskText, boost::posix_time::ptime startDateTime, boost::posix_time::ptime endDateTime) {
		_taskText = taskText;
		_startDateTime = startDateTime;
		_endDateTime = endDateTime;
	}

	std::string Task::getTaskText() {
		return _taskText;
	}

	bool Task::operator== (Task another) {
		if (this->_taskText != another._taskText) {
			return false;
		} else if (this->_startDateTime != another._startDateTime) {
			return false;
		} else if (this->_endDateTime != another._endDateTime) {
			return false;
		} else {
			return true;
		}
	}

	boost::posix_time::ptime Task::getStartDateTime() {
		return _startDateTime;
	}

	boost::posix_time::ptime Task::getEndDateTime() {
		return _endDateTime;
	}
