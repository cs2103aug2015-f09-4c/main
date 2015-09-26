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
	
	//for operation with either start or end dateTime, int is used as dummy variable in the meanwhile
	CommandTokens::CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, int dateTime) {
		_primaryCommandType = command1;
		_secondaryCommandType = command2;
		_details = details;
		_startDateTime = dateTime;
		_endDateTime = dateTime;
	}
	
	//for operation with both date and time, int is used as dummy variable in the meanwhile
	CommandTokens::CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, int startDateTime, int endDateTime) {
		_primaryCommandType = command1;
		_secondaryCommandType = command2;
		_details = details;
		_startDateTime = startDateTime;
		_endDateTime = endDateTime;
	}
	
	bool CommandTokens::isValid() {
		if (_primaryCommandType==Invalid) {
			return false;
		} 
		else {
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
	
	//int is used as dummy variable for dateTime
	int CommandTokens::getStartDateTime() {
		return _startDateTime;
	}
	
	int CommandTokens::getEndDateTime() {
		return _endDateTime;
	} 
