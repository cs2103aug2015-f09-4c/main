//@@author A0112218W

#include "Task.h"
#include <string>
using namespace API;

TASK_EXCEPTION::TASK_EXCEPTION(std::string message) : std::exception(message.c_str()){
}

TAG_LIMIT_EXCEPTION::TAG_LIMIT_EXCEPTION() : TASK_EXCEPTION(MESSAGE_TAG_LIMIT_REACHED.c_str()) {
}

Task::Task() {
}

Task::Task(std::string taskText) {
	try {
		checkIsValidName(taskText);
	} catch (TASK_EXCEPTION e) {
		throw e;
	}
	_taskText = taskText;
	_isComplete = false;
}

Task::Task(std::string taskText, ptime endDateTime) {
	try {
		checkIsValidName(taskText);
	} catch (TASK_EXCEPTION e) {
		throw e;
	}
	_taskText = taskText;
	_endDateTime = endDateTime;
	_isComplete = false;
}

Task::Task(std::string taskText, ptime startDateTime, ptime endDateTime) {
	try {
		checkIsValidName(taskText);
	} catch (TASK_EXCEPTION e) {
		throw e;
	}

	if (isEndLessThanStart(startDateTime,endDateTime)) {
		throw TASK_EXCEPTION(MESSAGE_END_LESS_THAN_START.c_str());
	} else if (endDateTime.is_special() && !startDateTime.is_special()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_END_DATE.c_str());
	}

	_taskText = taskText;
	_startDateTime = startDateTime;
	_endDateTime = endDateTime;
	_isComplete = false;
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

std::set<std::string>& Task::getTags(){
	return _tags;
}

bool Task::operator== (Task another) {
	if (this->_taskText != another._taskText) {
		return false;
	} else if (this->_startDateTime != another._startDateTime) {
		return false;
	} else if (this->_endDateTime != another._endDateTime) {
		return false;
	} else if (this->getTags() != another.getTags()) {
		return false;
	} else {
		return true;
	}
}

bool Task::isComplete(){
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

void Task::checkIsValidName(std::string name) {
	if (name.empty()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_TASK_TEXT.c_str());
	} else if (!std::isalnum(name[0])) {
		throw TASK_EXCEPTION(MESSAGE_INVALID_FIRST_CHARACTER.c_str());
	} else if (name.size() > MAX_TASK_NAME_LENGTH) {
		throw TASK_EXCEPTION(MESSAGE_LONG_TASK_TEXT.c_str());
	}
	return;
}

void Task::toggleComplete() {
	_isComplete = !_isComplete;
}

void Task::changeTaskText(std::string newTaskText) {
	try{
		checkIsValidName(newTaskText);
		_taskText = newTaskText;
	} catch (TASK_EXCEPTION e) {
		throw e;
	}
}

void Task::changeStartDateTime(ptime newStartDateTime) {
	if (isEndLessThanStart(newStartDateTime,_endDateTime)) {
		throw TASK_EXCEPTION(MESSAGE_END_LESS_THAN_START);
	} else if (!newStartDateTime.is_special() && _endDateTime.is_special()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_END_DATE);
	}

	_startDateTime = newStartDateTime;
}

void Task::changeEndDateTime(ptime newEndDateTime) {
	if (isEndLessThanStart(_startDateTime,newEndDateTime)) {
		throw TASK_EXCEPTION(MESSAGE_END_LESS_THAN_START);
	} else if (newEndDateTime.is_special() && !_startDateTime.is_special()) {
		throw TASK_EXCEPTION(MESSAGE_EMPTY_END_DATE);
	}

	_endDateTime = newEndDateTime;
}

void Task::addTag(std::string tag) {
	if (_tags.size() == MAX_TAG_NUM) {
		throw TAG_LIMIT_EXCEPTION();
	} else if (tag.size() > MAX_TAG_LENGTH) {
		throw TASK_EXCEPTION(MESSAGE_LONG_TAG);
	} else if (tag[0] != '#') {
		throw TASK_EXCEPTION(MESSAGE_TAG_FIRST_CHARACTER_NOT_HASH);
	}else if (_tags.find(tag) != _tags.end()) {
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

bool Task::sortByStartDateTimeAscending (Task task1, Task task2) {
	boost::posix_time::ptime startDateTime1 = task1.getStartDateTime();
	boost::posix_time::ptime startDateTime2 = task2.getStartDateTime();

	if (startDateTime1.is_special() && startDateTime2.is_special()) {
		return false;
	} else if (startDateTime1.is_special()) {
		return false;
	} else if (startDateTime2.is_special()) {
		return true;
	} else {
		return startDateTime1 < startDateTime2;
	}
}

bool Task::sortByEndDateTimeAscending (Task task1, Task task2) {
	boost::posix_time::ptime endDateTime1 = task1.getEndDateTime();
	boost::posix_time::ptime endDateTime2 = task2.getEndDateTime();

	if (endDateTime1.is_special() && endDateTime2.is_special()) {
		return false;
	} else if (endDateTime1.is_special()) {
		return false;
	} else if (endDateTime2.is_special()) {
		return true;
	} else {
		return endDateTime1 < endDateTime2;
	}
}

bool Task::sortByNameAscending (Task task1, Task task2) {
	std::string task1Text = task1.getTaskText();
	std::string task2Text = task2.getTaskText();

	size_t minStringLength = (std::min)(task1Text.size(), task2Text.size());

	for (size_t i = 0 ; i < minStringLength ; ++i) {
		task1Text[i] = std::tolower(task1Text[i]);
		task2Text[i] = std::tolower(task2Text[i]);
	}

	for (size_t i = 0 ; i < minStringLength ; ++i) {
		if (task1Text[i] < task2Text[i]) {
			return true;
		} else if (task1Text[i] > task2Text[i]) {
			return false;
		}
	}

	if (task1Text.size() < task2Text.size()) {
		return true;
	} else {
		return false;
	}
}

bool Task::sortByStartDateTimeDescending (Task task1, Task task2) {
	boost::posix_time::ptime startDateTime1 = task1.getStartDateTime();
	boost::posix_time::ptime startDateTime2 = task2.getStartDateTime();

	if (startDateTime1.is_special() && startDateTime2.is_special()) {
		return false;
	} else if (startDateTime1.is_special()) {
		return false;
	} else if (startDateTime2.is_special()) {
		return true;
	} else {
		return startDateTime1 > startDateTime2;
	}		
}

bool Task::sortByEndDateTimeDescending (Task task1, Task task2) {
	boost::posix_time::ptime endDateTime1 = task1.getEndDateTime();
	boost::posix_time::ptime endDateTime2 = task2.getEndDateTime();

	if (endDateTime1.is_special() && endDateTime2.is_special()) {
		return false;
	} else if (endDateTime1.is_special()) {
		return false;
	} else if (endDateTime2.is_special()) {
		return true;
	} else {
		return endDateTime1 > endDateTime2;
	}
}

bool Task::sortByNameDescending(Task task1, Task task2) {
	std::string task1Text = task1.getTaskText();
	std::string task2Text = task2.getTaskText();

	size_t minStringLength = (std::min)(task1Text.size(), task2Text.size());

	for (size_t i = 0 ; i < minStringLength ; ++i) {
		task1Text[i] = std::tolower(task1Text[i]);
		task2Text[i] = std::tolower(task2Text[i]);
	}

	for (size_t i = 0 ; i < minStringLength ; ++i) {
		if (task1Text[i] > task2Text[i]) {
			return true;
		} else if (task1Text[i] < task2Text[i]) {
			return false;
		}
	}

	if (task1Text.size() < task2Text.size()) {
		return true;
	} else {
		return false;
	}	
}