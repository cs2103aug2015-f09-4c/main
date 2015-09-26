#pragma once

// TODO this include may not belong here, move it
#include "boost/date_time/posix_time/posix_time.hpp"


class Task
{
public:
	Task(std::string taskText, int startDateTime, int endDateTime);
	std::string getTaskText();

	//int to be replace by dateTime object
	int getStartDateTime();
	int getEndDateTime();
	
private:
	std::string _taskText;
	
	//dateTime object to be specified, use int as dummy variable
	int _startDateTime;
	int _endDateTime;
};

