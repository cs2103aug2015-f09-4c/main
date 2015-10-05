#include "Task.h"
#include <string>
using namespace API;

Task::Task() {
	_taskText = "";
	_isComplete = false;
}

Task::Task(std::string taskText) {
	_taskText = taskText;
	_isComplete = false;
}

Task::Task(std::string taskText, boost::posix_time::ptime endDateTime) {
	_taskText = taskText;
	_endDateTime = endDateTime;
	_isComplete = false;
}

Task::Task(std::string taskText, boost::posix_time::ptime startDateTime, boost::posix_time::ptime endDateTime) {
	_taskText = taskText;
	_startDateTime = startDateTime;
	_endDateTime = endDateTime;
	_isComplete = false;
}

std::string Task::getTaskText() {
	return _taskText;
}

boost::posix_time::ptime Task::getStartDateTime() {
	return _startDateTime;
}

boost::posix_time::ptime Task::getEndDateTime() {
	return _endDateTime;
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

bool Task::isValid() {
	if (_taskText.size() < 1) {
		return false;
	} else {
		return true;
	}
}

bool Task::isComplete() {
	return _isComplete;
}

void Task::setComplete() {
	_isComplete = true;
}

void Task::changeTaskText(std::string newTaskText) {
	_taskText = newTaskText;
}

void Task::changeStartDateTime(boost::posix_time::ptime newStartDateTime) {
	_startDateTime = newStartDateTime;
}

void Task::changeEndDateTime(boost::posix_time::ptime newEndDateTime) {
	_endDateTime = newEndDateTime;
}