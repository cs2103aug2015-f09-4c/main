#pragma once

#include <vector>
#include <string>
#include "../boost/date_time/posix_time/posix_time.hpp"

// Command Type for main groups of operation
enum PrimaryCommandType {
	Invalid, Add, Display, Edit , Delete
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
	std::vector<std::string> _details;

	//dateTime object to be specified later, int is used as dummy variable in the meanwhile
	boost::posix_time::ptime _startDateTime;
	boost::posix_time::ptime _endDateTime;

public:
	//default constructor, used for invalid command
	CommandTokens();

	//for operation without date and time
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details);

	//for operation with either start or end dateTime, int is used as dummy variable in the meanwhile
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, boost::posix_time::ptime dateTime);

	//for operation with both date and time, int is used as dummy variable in the meanwhile
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, boost::posix_time::ptime startDateTime, boost::posix_time::ptime endDateTime);

	bool isValid();

	PrimaryCommandType getPrimaryCommand();

	SecondaryCommandType getSecondaryCommand();

	std::vector<std::string>& getDetails();

	//int is used as dummy variable for dateTime
	boost::posix_time::ptime getStartDateTime();

	boost::posix_time::ptime getEndDateTime();
};

