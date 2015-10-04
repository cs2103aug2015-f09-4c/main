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
	None, Floating, Timed, Todo, All, Complete, Incomplete, Index, Name, Start, End
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
	boost::posix_time::ptime getStartDateTime();
	boost::posix_time::ptime getEndDateTime();
	int getIndex();

	void setPrimaryCommand(PrimaryCommandType newPrimaryCommand);
	void setSecondaryCommand(SecondaryCommandType newSecondaryCommand);
	void setTaskName(std::string newTaskName);
	void setDetails(std::vector< std::string > newDetails);
	void setStartDateTime(boost::posix_time::ptime newStartDateTime);
	void setEndDateTime(boost::posix_time::ptime newEndDateTime);
	void setIndex(int newIndex);

private:
	PrimaryCommandType _primaryCommandType;
	SecondaryCommandType _secondaryCommandType;
	std::string _taskName;
	std::vector<std::string> _details;
	boost::posix_time::ptime _startDateTime;
	boost::posix_time::ptime _endDateTime;
	int _index;
};