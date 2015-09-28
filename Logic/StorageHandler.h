#ifndef STORAGE_HANDLER_H
#define STORAGE_HANDLER_H

#include <fstream>
#include <algorithm>
#include "..\APIContracts\CommandTokens.h"
#include "..\APIContracts\Task.h"
#include "..\APIContracts\UIFeedback.h"
using namespace Swiftask;

enum Display_Type {
	Display_All, Display_By_Name, Display_By_Start, Display_By_End
};

const std::string MESSAGE_ADD_SUCCESS = "\"%s\" have been added succesfully.\nStart Date Time: %s\nEnd Date Time: %s"; 
const std::string MESSAGE_ADD_EMPTY = "Task text cannot be empty.";
const std::string MESSAGE_ADD_DUPLICATE = "Duplicate task is found. New task is not added.";

class StorageHandler {
private:
	std::vector<Task> Tasks;
	std::vector<Task> TasksToDisplay;
	std::string _fileName;

	//save and load are to be supported after we determine the save file format
	//below are template assuming save file is in txt format.
	/*
	void loadFromSaveFile(std::string fileName) {
		saveToSaveFile(_fileName);
		Tasks.clear();
		std::ifstream loadFile(fileName);
		if (loadFile.is_open()) {
			while (!loadFile.eof())
			{
				std::string taskText;
				std::string startDateTimeString;
				std::string endDateTimeString;
				
				std::getline(loadFile,taskText);
				
				std::getline(loadFile,startDateTimeString);
				boost::posix_time::ptime startDateTime = boost::posix_time::time_from_string(startDateTimeString);
				
				std::getline(loadFile,endDateTimeString);
				boost::posix_time::ptime endDateTime = boost::posix_time::time_from_string(endDateTimeString);
				
				Tasks.push_back(Task(taskText, startDateTime, endDateTime));
			}
		}
	}
	*/

	/*
	void saveToSaveFile(std::string fileName) {
		std::ofstream saveFile(fileName);
		for (size_t i = 0 ; i < Tasks.size() ; ++i) {
			saveFile << Tasks[i].getTaskText() << "\n";
			saveFile << boost::posix_time::to_simple_string(Tasks[i].getStartDateTime()) << "\n";
			saveFile << boost::posix_time::to_simple_string(Tasks[i].getEndDateTime()) << "\n";
		}
		return;
	}
	*/

	bool isContain(Task task) {
		if (std::find(Tasks.begin(), Tasks.end(), task) == Tasks.end()) {
			return false;
		} else {
			return true;
		}
	}

	void findConflict(std::string& feedbackMessage, Task task) {
		for (int i = 0 ; i < Tasks.size() ; ++i) {
		}
	}

public:
	StorageHandler(std::string fileName){
		_fileName = fileName;

		//to be included after we finalized save file format
		//loadFromSaveFile(_fileName);
	}

	std::vector<Task>& getAllTasks() {
		return Tasks;
	}

	std::vector<Task>& getTasksToDisplay() {
		return Tasks;
	}

	std::string add(Task task) {
		std::string feedbackMessage;

		//Empty task text is not allowed.
		if (task.getTaskText().size() < 1) {
			feedbackMessage = MESSAGE_ADD_EMPTY;
		} else if (!isContain(task)) {
			Tasks.push_back(task);
			std::string taskText = task.getTaskText();
			std::string startDateTime = boost::posix_time::to_simple_string(task.getStartDateTime());
			std::string endDateTime = boost::posix_time::to_simple_string(task.getEndDateTime());
			char buffer[255];
			sprintf_s(buffer, MESSAGE_ADD_SUCCESS.c_str(), taskText, startDateTime, endDateTime);
			feedbackMessage = std::string(buffer);
			 
		} else {
			feedbackMessage = MESSAGE_ADD_DUPLICATE; 
		}
		return feedbackMessage;
	}

	std::vector<Task> remove(Task task) {
		//to do
		return Tasks;
	}

	std::vector<Task> getDisplay(Display_Type type) {
		//to do
		return Tasks;
	}	
};

#endif