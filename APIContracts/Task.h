#pragma once

// TODO this include may not belong here, move it
#include "boost/date_time/posix_time/posix_time.hpp"


class Task
{
public:
	Task(std::string taskText, boost::posix_time::ptime startDateTime, boost::posix_time::ptime endDateTime);
	std::string getTaskText();

	//int to be replace by dateTime object
	boost::posix_time::ptime getStartDateTime();
	boost::posix_time::ptime getEndDateTime();
	
private:
	std::string _taskText;
	
	//dateTime object to be specified, use int as dummy variable
	boost::posix_time::ptime _startDateTime;
	boost::posix_time::ptime _endDateTime;
};

