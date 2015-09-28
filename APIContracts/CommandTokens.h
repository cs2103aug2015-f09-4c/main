#pragma once

#include <vector>
#include <string>
#include "../boost/date_time/posix_time/posix_time.hpp"

// Command Type for main groups of operation
enum PrimaryCommandType {
	Invalid, Add, Display, Edit, Delete, Help
};

// Command Type to further specify the operation
enum SecondaryCommandType {
	None, Floating, Timed, Todo, All, Complete, Incomplete
};

class CommandTokens
{
private:
	PrimaryCommandType _primaryCommandType;
	SecondaryCommandType _secondaryCommandType;
	std::string _taskName;
	std::vector<std::string> _details;
	boost::posix_time::ptime _startDateTime;
	boost::posix_time::ptime _endDateTime;

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

	PrimaryCommandType getPrimaryCommand();
	void setPrimaryCommand(PrimaryCommandType newPrimaryCommand);

	SecondaryCommandType getSecondaryCommand();
	void setSecondaryCommand(SecondaryCommandType newSecondaryCommand);

	std::string getTaskName();
	void setTaskName(std::string newTaskName);

	std::vector<std::string>& getDetails();
	void setDetails(std::vector< std::string > newDetails);

	boost::posix_time::ptime getStartDateTime();
	void setStartDateTime(boost::posix_time::ptime newStartDateTime);

	boost::posix_time::ptime getEndDateTime();
	void setEndDateTime(boost::posix_time::ptime newEndDateTime);
};
