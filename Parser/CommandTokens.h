#pragma once
#include <vector>
#include "../boost/date_time/posix_time/posix_time.hpp"

// Command Type for main groups of operation
enum PrimaryCommandType {
	Add,
	Complete,
	Delete,
	Display,
	Edit,
	Help,
	Invalid,
	Undo
};

// Command Type to further specify the operation
enum SecondaryCommandType {
	All,
	End,
	Floating,
	Index,
	Name,
	None,
	Start,
	Timed,
	Todo
};

class CommandTokens {
public:
	//default constructor, used for invalid command
	CommandTokens();

	//Constructor for operation without date and time
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details);

	//Constructor for operation with either start or end dateTime
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, boost::posix_time::ptime dateTime);

	//Constructor for operation with both date and time
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, boost::posix_time::ptime startDateTime, boost::posix_time::ptime endDateTime);

	bool isValid();
	void resetMemberVariables();

	PrimaryCommandType getPrimaryCommand();
	SecondaryCommandType getSecondaryCommand();
	std::string getTaskName();
	std::vector<std::string>& getDetails();
	std::vector<std::string>& getTags();
	boost::posix_time::ptime getStartDateTime();
	boost::posix_time::ptime getEndDateTime();
	int getIndex();

	void setPrimaryCommand(PrimaryCommandType newPrimaryCommand);
	void setSecondaryCommand(SecondaryCommandType newSecondaryCommand);
	void setTaskName(std::string newTaskName);
	void setDetails(std::vector<std::string> newDetails);
	void setTags(std::vector<std::string> newTags);
	void setStartDateTime(boost::posix_time::ptime newStartDateTime);
	void setEndDateTime(boost::posix_time::ptime newEndDateTime);
	void setIndex(int newIndex);

private:
	PrimaryCommandType _primaryCommandType;
	SecondaryCommandType _secondaryCommandType;
	std::string _taskName;
	std::vector<std::string> _details;
	std::vector<std::string> _tags;
	boost::posix_time::ptime _startDateTime;
	boost::posix_time::ptime _endDateTime;
	int _index;
};
