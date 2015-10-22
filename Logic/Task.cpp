#include "Task.h"
#include <string>
using namespace API;

TASK_EXCEPTION::TASK_EXCEPTION(std::string message) : std::exception(message.c_str()){
}

Task::Task() {
	_taskText = "";
	_isComplete = false;
}

Task::Task(std::string taskText) {
	if (taskText.empty()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_TASK_TEXT.c_str());
	}
	_taskText = taskText;
	_isComplete = false;
}

Task::Task(std::string taskText, boost::posix_time::ptime endDateTime) {
	if (taskText.empty()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_TASK_TEXT.c_str());
	}
	_taskText = taskText;
	_endDateTime = endDateTime;
	_isComplete = false;
}

Task::Task(std::string taskText, boost::posix_time::ptime startDateTime, boost::posix_time::ptime endDateTime) {
	if (taskText.empty()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_TASK_TEXT.c_str());
	} else if (isEndLessThanStart(startDateTime,endDateTime)) {
		throw TASK_EXCEPTION(MESSAGE_END_LESS_THAN_START.c_str());
	} else if (endDateTime.is_special() && !startDateTime.is_special()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_END_DATE.c_str());
	}
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

std::set<std::string>& Task::getTags() {
	return _tags;
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

bool Task::isEndLessThanStart(boost::posix_time::ptime start, boost::posix_time::ptime end) {
	if (start.is_special()) {
		return false;
	} else if (end.is_special()) {
		return false;
	} else {
		return end < start;
	}
}

void Task::toggleComplete() {
	_isComplete = !_isComplete;
}

void Task::changeTaskText(std::string newTaskText) {
	if (newTaskText.empty()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_TASK_TEXT.c_str());
	}
	_taskText = newTaskText;
}

void Task::changeStartDateTime(boost::posix_time::ptime newStartDateTime) {
	if (isEndLessThanStart(newStartDateTime,_endDateTime)) {
		throw TASK_EXCEPTION(MESSAGE_END_LESS_THAN_START.c_str());
	} else if (!newStartDateTime.is_special() && _endDateTime.is_special()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_END_DATE.c_str());
	}
	_startDateTime = newStartDateTime;
}

void Task::changeEndDateTime(boost::posix_time::ptime newEndDateTime) {
	if (isEndLessThanStart(_startDateTime,newEndDateTime)) {
		throw TASK_EXCEPTION(MESSAGE_END_LESS_THAN_START.c_str());
	} else if (newEndDateTime.is_special() && !_startDateTime.is_special()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_END_DATE.c_str());
	}

	_endDateTime = newEndDateTime;
}

bool Task::addTag(std::string tag) {
	if (_tags.find(tag) == _tags.end()) {
		_tags.insert(tag);
		return true;
	} else {
		return false;
	}
}

void Task::removeTag(std::string tag) {
	std::set<std::string>::iterator iter = _tags.find(tag);
	if (iter == _tags.end()) {
		throw TASK_EXCEPTION(MESSAGE_TAG_NOT_FOUND);
	} else {
		_tags.erase(iter);
	}
}