#include <vector>
#include <string>

// Command Type for main groups of operation
enum PrimaryCommandType {
	Invalid, Add, Display, Edit , Delete
};

// Command Type to further specify the operation
enum SecondaryCommandType {
	None, Floating, Timed, Todo, All, Complete, Incomplete
};

// Return object by parser to logic after user input is parsed
class CommandTokens {
private:
	
	PrimaryCommandType _primaryCommandType;
	SecondaryCommandType _secondaryCommandType;
	vector<string> _details;
	
	//dateTime object to be specified later, int is used as dummy variable in the meanwhile 
	int _startDateTime;
	int _endDateTime;

public:
	//default constructor, used for invalid command
	CommandTokens() { 
		_primaryCommandType = Invalid;
	}
	
	//for operation without date and time
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, vector<string> details) {
		_primaryCommandType = command1;
		_secondaryCommandType = command2;
		_details = details;
	}
	
	//for operation with either start or end dateTime, int is used as dummy variable in the meanwhile
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, vector<string> details, int dateTime) {
		_primaryCommandType = command1;
		_secondaryCommandType = command2;
		_details = details;
		_startDateTime = dateTime;
		_endDateTime = dateTime;
	}
	
	//for operation with both date and time, int is used as dummy variable in the meanwhile
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, vector<string> details, int startDateTime, int endDateTime) {
		_primaryCommandType = command1;
		_secondaryCommandType = command2;
		_details = details;
		_startDateTime = startDateTime;
		_endDateTime = endDateTime;
	}
	
	bool isValid() {
		if (_primaryCommandType==Invalid) {
			return false;
		} 
		else {
			return true;
		}
	}
	
	PrimaryCommandType getPrimaryCommand() {
		return _primaryCommandType;
	}
	
	SecondaryCommandType getSecondaryCommand() {
		return _secondaryCommandType;
	}
	
	vector<string>& getDetails() {
		return _details;
	}
	
	//int is used as dummy variable for dateTime
	int getStartDateTime() {
		return startDateTime;
	}
	
	int getEndDateTime() {
		return endDateTime;
	} 
	
	
	
	
	
}

