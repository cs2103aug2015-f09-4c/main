#include "CommandTokens.h"

//default constructor, used for invalid command
CommandTokens::CommandTokens() {
	resetMemberVariables();
}

//for operation without date and time
CommandTokens::CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details) {
	_primaryCommandType = command1;
	_secondaryCommandType = command2;
	_details = details;
}

//for operation with either start or end dateTime
CommandTokens::CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, boost::posix_time::ptime dateTime) {
	_primaryCommandType = command1;
	_secondaryCommandType = command2;
	_details = details;
	_startDateTime = dateTime;
	_endDateTime = dateTime;
}

//for operation with both start and end dateTime
CommandTokens::CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, boost::posix_time::ptime startDateTime, boost::posix_time::ptime endDateTime) {
	_primaryCommandType = command1;
	_secondaryCommandType = command2;
	_details = details;
	_startDateTime = startDateTime;
	_endDateTime = endDateTime;
}

bool CommandTokens::isValid() {
	if (_primaryCommandType==Invalid) {
		return false;
	} else {
		return true;
	}
}

PrimaryCommandType CommandTokens::getPrimaryCommand() {
	return _primaryCommandType;
}

SecondaryCommandType CommandTokens::getSecondaryCommand() {
	return _secondaryCommandType;
}

std::string CommandTokens::getTaskName() {
	return _taskName;
}

std::vector<std::string>& CommandTokens::getDetails() {
	return _details;
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

void CommandTokens::setPrimaryCommand(PrimaryCommandType newPrimaryCommand) {
	_primaryCommandType = newPrimaryCommand;
}

void CommandTokens::setSecondaryCommand(SecondaryCommandType newSecondaryCommand) {
	_secondaryCommandType = newSecondaryCommand;
}

void CommandTokens::setTaskName(std::string newTaskName) {
	_taskName = newTaskName;
}

void CommandTokens::setDetails(std::vector< std::string > newDetails) {
	_details = newDetails;
}

void CommandTokens::setTags(std::vector< std::string > newTags) {
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

void CommandTokens::resetMemberVariables() {
	_primaryCommandType = Invalid;
	_secondaryCommandType = None;
	_taskName = "";
	_details.clear();
	_index = -1;

	boost::posix_time::ptime notAPtime;
	_startDateTime = notAPtime;
	_endDateTime = notAPtime;
}