#pragma once

// TODO this include may not belong here, move it
#include "../boost/date_time/posix_time/posix_time.hpp"

namespace API{
class Task
{
public:
	//Constructor for invalid task
	Task();

	//Constructor for floating task
	Task(std::string taskText);

	//Constructor for toDo task
	Task(std::string taskText, boost::posix_time::ptime endDateTime);

	//Constructor for timed task
	Task(std::string taskText, boost::posix_time::ptime startDateTime, boost::posix_time::ptime endDateTime);

	//Getters
	std::string getTaskText();
	boost::posix_time::ptime getStartDateTime();
	boost::posix_time::ptime getEndDateTime();

	//Methods
	bool operator==(Task another);
	bool isValid();

private:
	std::string _taskText;
	boost::posix_time::ptime _startDateTime;
	boost::posix_time::ptime _endDateTime;
};
}
