#include "Task.h"
#include <string>
using namespace API;

TASK_EXCEPTION::TASK_EXCEPTION(std::string message) : std::exception(message.c_str()){
}

TAG_LIMIT_EXCEPTION::TAG_LIMIT_EXCEPTION() : TASK_EXCEPTION(MESSAGE_TAG_LIMIT_REACHED.c_str()) {
}

DUPLICATE_TAG_EXCEPTION::DUPLICATE_TAG_EXCEPTION(std::string message) : TASK_EXCEPTION(message.c_str()) {
}

Task::Task() {
}

Task::Task(std::string taskText) {
	try {
		if (isValidName(taskText)) {
			_taskText = taskText;
			_isComplete = false;
		}
	} catch (TASK_EXCEPTION e) {
		throw e;
	}
}

Task::Task(std::string taskText, ptime endDateTime) {
	try {
		if (isValidName(taskText)) {
			_taskText = taskText;
			_endDateTime = endDateTime;
			_isComplete = false;
		}
	} catch (TASK_EXCEPTION e) {
		throw e;
	}
}

Task::Task(std::string taskText, ptime startDateTime, ptime endDateTime) {
	if (isEndLessThanStart(startDateTime,endDateTime)) {
		throw TASK_EXCEPTION(MESSAGE_END_LESS_THAN_START.c_str());
	} else if (endDateTime.is_special() && !startDateTime.is_special()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_END_DATE.c_str());
	}

	try {
		if (isValidName(taskText)) {
			_taskText = taskText;
			_startDateTime = startDateTime;
			_endDateTime = endDateTime;
			_isComplete = false;
		}
	} catch (TASK_EXCEPTION e) {
		throw e;
	}

}

bool Task::isValid() {
	return _taskText.size() > 0;
}

std::string Task::getTaskText() {
	return _taskText;
}

ptime Task::getStartDateTime() {
	return _startDateTime;
}

ptime Task::getEndDateTime() {
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

bool Task::isComplete() {
	return _isComplete;
}

bool Task::isEndLessThanStart(ptime start, ptime end) {
	if (start.is_special()) {
		return false;
	} else if (end.is_special()) {
		return false;
	} else {
		return end < start;
	}
}

bool Task::isValidName(std::string name) {
	if (name.empty()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_TASK_TEXT.c_str());
	} else if (!std::isalnum(name[0])) {
		throw TASK_EXCEPTION(MESSAGE_INVALID_FIRST_CHARACTER.c_str());
	} else if (name.size() > MAX_TASK_NAME_LENGTH) {
		throw TASK_EXCEPTION(MESSAGE_LONG_TASK_TEXT.c_str());
	} else {
		return true;
	}
}

void Task::toggleComplete() {
	_isComplete = !_isComplete;
}

void Task::changeTaskText(std::string newTaskText) {
	try{
		if (isValidName(newTaskText)) {
			_taskText = newTaskText;
		}
	} catch (TASK_EXCEPTION e) {
		throw e;
	}
}

void Task::changeStartDateTime(ptime newStartDateTime) {
	if (isEndLessThanStart(newStartDateTime,_endDateTime)) {
		throw TASK_EXCEPTION(MESSAGE_END_LESS_THAN_START.c_str());
	} else if (!newStartDateTime.is_special() && _endDateTime.is_special()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_END_DATE.c_str());
	}

	_startDateTime = newStartDateTime;
}

void Task::changeEndDateTime(ptime newEndDateTime) {
	if (isEndLessThanStart(_startDateTime,newEndDateTime)) {
		throw TASK_EXCEPTION(MESSAGE_END_LESS_THAN_START.c_str());
	} else if (newEndDateTime.is_special() && !_startDateTime.is_special()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_END_DATE.c_str());
	}

	_endDateTime = newEndDateTime;
}

void Task::addTag(std::string tag) {
	if (_tags.size() == MAX_TAG_NUM) {
		throw TAG_LIMIT_EXCEPTION();
	} else if (_tags.find(tag) != _tags.end()) {
		char buffer[255];
		sprintf_s(buffer, MESSAGE_DUPLICATE_TAG.c_str(), tag.c_str());
		throw TASK_EXCEPTION(buffer);
	} else {
		_tags.insert(tag);
		return;
	}
}

void Task::removeTag(std::string tag) {
	std::set<std::string>::iterator iter = _tags.find(tag);
	if (iter == _tags.end()) {
		char buffer[255];
		sprintf_s(buffer, MESSAGE_TAG_NOT_FOUND.c_str(), tag.c_str());
		throw TASK_EXCEPTION(buffer);
	} else {
		_tags.erase(iter);
	}
}