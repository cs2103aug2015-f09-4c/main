#ifndef SWIFT_TASK_H_
#define SWIFT_TASK_H_ 

#include <vector>
#include <string>
//#include "boost/date_time/posix_time/posix_time.hpp"

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
	std::vector<std::string> _details;
	
	//dateTime object to be specified later, int is used as dummy variable in the meanwhile 
	int _startDateTime;
	int _endDateTime;

public:
	//default constructor, used for invalid command
	CommandTokens() { 
		_primaryCommandType = Invalid;
	}
	
	//for operation without date and time
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details) {
		_primaryCommandType = command1;
		_secondaryCommandType = command2;
		_details = details;
	}
	
	//for operation with either start or end dateTime, int is used as dummy variable in the meanwhile
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, int dateTime) {
		_primaryCommandType = command1;
		_secondaryCommandType = command2;
		_details = details;
		_startDateTime = dateTime;
		_endDateTime = dateTime;
	}
	
	//for operation with both date and time, int is used as dummy variable in the meanwhile
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, int startDateTime, int endDateTime) {
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
	
	std::vector<std::string>& getDetails() {
		return _details;
	}
	
	//int is used as dummy variable for dateTime
	int getStartDateTime() {
		return _startDateTime;
	}
	
	int getEndDateTime() {
		return _endDateTime;
	} 
};

class Task{
private:
	std::string _taskText;
	
	//dateTime object to be specified, use int as dummy variable
	int _startDateTime;
	int _endDateTime;

public:
	Task() {
		_taskText = "";
		_startDateTime = -1;
		_endDateTime = -1;
	}

	Task(std::string taskText) {
		_taskText = taskText;
		//invalid date time to indicate no date time
		_startDateTime = -1;
		_endDateTime = -1;
	}

	Task(std::string taskText, int endDateTime) {
		_taskText = taskText;
		_endDateTime = endDateTime;
		//invalid date time to indicate no start date time
		_startDateTime = -1;
	}

	Task(std::string taskText, int startDateTime, int endDateTime) {
		_taskText = taskText;
		_startDateTime = startDateTime;
		_endDateTime = endDateTime;
	}

	std::string getTaskText() {
		return _taskText;
	}

	//int to be replace by dateTime object
	int getStartDateTime() {
		return _startDateTime;
	}

	int getEndDateTime() {
		return _endDateTime;
	}
};

class UIFeedback{
private:
	std::vector<Task> _tasksForDisplay;
	std::string _feedbackMessage;
public:
	UIFeedback() {
	}

	UIFeedback(std::vector<Task>& tasksForDisplay, std::string feedbackMessage) {
		_tasksForDisplay = tasksForDisplay;
		_feedbackMessage = feedbackMessage;
	}

	std::vector<Task>& getTasksForDisplay() {
		return _tasksForDisplay;
	}

	std::string getFeedbackMessage() {
		return _feedbackMessage;
	}
};

#endif

