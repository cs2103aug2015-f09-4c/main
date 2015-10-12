#include "PhysicalStorageHandler.h"


PhysicalStorageHandler::PhysicalStorageHandler() {
}


PhysicalStorageHandler::~PhysicalStorageHandler(void)
{
}

void PhysicalStorageHandler::loadFromFile(std::vector<API::Task>& tasks, std::string filePath) {
	tasks.clear();
	std::ifstream loadFile(filePath.c_str());
	if (loadFile.is_open()) {
		
		while (!loadFile.eof())
		{
			std::string taskText;
			std::string startDateTimeString;
			std::string endDateTimeString;
			std::string isCompleteString;

			std::getline(loadFile,taskText);
			if (taskText.empty()) {
				break;
			}

			std::getline(loadFile,startDateTimeString);
			boost::posix_time::ptime startDateTime;
			if (startDateTimeString != "not-a-date-time") {
				startDateTime = boost::posix_time::time_from_string(startDateTimeString);
			}

			std::getline(loadFile,endDateTimeString);
			boost::posix_time::ptime endDateTime;
			if (endDateTimeString != "not-a-date-time") {
				endDateTime = boost::posix_time::time_from_string(endDateTimeString);
			}

			std::getline(loadFile, isCompleteString);

			API::Task taskToAdd(taskText, startDateTime, endDateTime);
			if (isCompleteString == "1") {
				taskToAdd.setComplete();
			}

			tasks.push_back(taskToAdd);
		}
	}
}

void PhysicalStorageHandler::saveToFile(std::vector<API::Task>& tasks, std::string filePath) {
	std::ofstream saveFile(filePath.c_str());
	for (size_t i = 0 ; i < tasks.size() ; ++i) {
		saveFile << tasks[i].getTaskText() << "\n";
		saveFile << boost::posix_time::to_simple_string(tasks[i].getStartDateTime()) << "\n";
		saveFile << boost::posix_time::to_simple_string(tasks[i].getEndDateTime()) << "\n";
		if (tasks[i].isComplete()) {
			saveFile << "1\n";
		} else {
			saveFile << "0\n";
		}
	}
	return;
}