#include "CommandTokens.h"

	//default constructor, used for invalid command
	CommandTokens::CommandTokens() { 
		_primaryCommandType = Invalid;
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
	
	std::vector<std::string>& CommandTokens::getDetails() {
		return _details;
	}
	
	boost::posix_time::ptime CommandTokens::getStartDateTime() {
		return _startDateTime;
	}
	
	boost::posix_time::ptime CommandTokens::getEndDateTime() {
		return _endDateTime;
	} 
