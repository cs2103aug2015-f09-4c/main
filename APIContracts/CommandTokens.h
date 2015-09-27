#pragma once

#include <vector>
#include <string>

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
public:
	//default constructor, used for invalid command
	CommandTokens();

	//for operation without date and time
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details);

	//for operation with either start or end dateTime, int is used as dummy variable in the meanwhile
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, int dateTime);

	//for operation with both date and time, int is used as dummy variable in the meanwhile
	CommandTokens(PrimaryCommandType command1, SecondaryCommandType command2, std::vector<std::string> details, int startDateTime, int endDateTime);

	bool isValid();

	PrimaryCommandType getPrimaryCommand();
	void setPrimaryCommand(PrimaryCommandType newPrimaryCommand);

	SecondaryCommandType getSecondaryCommand();
	void setSecondaryCommand(SecondaryCommandType newSecondaryCommand);

	std::string getTaskName();
	void setTaskName(std::string newTaskName);

	std::vector<std::string>& getDetails();
	void setDetails(std::vector< std::string > newDetails);

	//int is used as dummy variable for dateTime
	int getStartDateTime();
	void setStartDateTime(int newStartDateTime);

	int getEndDateTime();
	void setEndDateTime(int newEndDateTime);

private:
	PrimaryCommandType _primaryCommandType;
	SecondaryCommandType _secondaryCommandType;
	std::string _taskName;
	std::vector<std::string> _details;

	//dateTime object to be specified later, int is used as dummy variable in the meanwhile
	int _startDateTime;
	int _endDateTime;
};