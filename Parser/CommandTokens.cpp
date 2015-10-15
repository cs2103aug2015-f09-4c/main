#include "CommandTokens.h"

// complete constructor, with default arguments initialised to sentinel values
CommandTokens::CommandTokens(PrimaryCommandType primaryCommandType,
                             SecondaryCommandType secondaryCommandType,
                             std::string taskName,
                             boost::posix_time::ptime startDateTime,
                             boost::posix_time::ptime endDateTime,
                             std::vector<std::string> tags,
                             int index) :
	_primaryCommandType(primaryCommandType),
	_secondaryCommandType(secondaryCommandType),
	_taskName(taskName),
	_startDateTime(startDateTime),
	_endDateTime(endDateTime),
	_tags(tags),
	_index(index) {
}

void CommandTokens::resetMemberVariables() {
	_primaryCommandType = Invalid;
	_secondaryCommandType = None;
	_taskName = "";
	_tags.clear();
	_index = -1;

	boost::posix_time::ptime notAPtime;
	_startDateTime = notAPtime;
	_endDateTime = notAPtime;
}

bool CommandTokens::isValid() {
	return _primaryCommandType == Invalid;
}

// getters
PrimaryCommandType CommandTokens::getPrimaryCommand() {
	return _primaryCommandType;
}

SecondaryCommandType CommandTokens::getSecondaryCommand() {
	return _secondaryCommandType;
}

std::string CommandTokens::getTaskName() {
	return _taskName;
}

std::vector<std::string>& CommandTokens::getTags() {
	return _tags;
}

boost::posix_time::ptime CommandTokens::getStartDateTime() {
	return _startDateTime;
}

boost::posix_time::ptime CommandTokens::getEndDateTime() {
	return _endDateTime;
}

int CommandTokens::getIndex() {
	return _index;
}

// setters
void CommandTokens::setPrimaryCommand(PrimaryCommandType newPrimaryCommand) {
	_primaryCommandType = newPrimaryCommand;
}

void CommandTokens::setSecondaryCommand(SecondaryCommandType newSecondaryCommand) {
	_secondaryCommandType = newSecondaryCommand;
}

void CommandTokens::setTaskName(std::string newTaskName) {
	_taskName = newTaskName;
}

void CommandTokens::setTags(std::vector<std::string> newTags) {
	_tags = newTags;
}

void CommandTokens::setStartDateTime(boost::posix_time::ptime newStartDateTime) {
	_startDateTime = newStartDateTime;
}

void CommandTokens::setEndDateTime(boost::posix_time::ptime newEndDateTime) {
	_endDateTime = newEndDateTime;
}

void CommandTokens::setIndex(int newIndex) {
	_index = newIndex;
}
