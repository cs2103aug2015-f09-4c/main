#ifndef STORAGE_HANDLER_H
#define STORAGE_HANDLER_H

#include <fstream>
#include "..\APIContracts\CommandTokens.h"
#include "..\APIContracts\Task.h"
#include "..\APIContracts\UIFeedback.h"
#include "Logic.h"

class StorageHandler {
private:
	std::vector<Task> Tasks;
	std::string _fileName;

	void loadFromSaveFile(std::string fileName) {
		std::ifstream loadFile(fileName);
		if (loadFile.is_open()) {
			while (!loadFile.eof())
			{
				std::string task;
				std::string startDateTimeString;
				std::string endDateTimeString;
				std::getline(loadFile,task);
				std::getline(loadFile,startDateTimeString);
				std::getline(loadFile,endDateTimeString);
			}
		}
	}

	void saveToSaveFile(std::string fileName) {
		std::ofstream saveFile(fileName);
		for (size_t i = 0 ; i < Tasks.size() ; ++i) {
			saveFile << Tasks[i].getTaskText() << "\n";
		}
		return;
	}

public:
	StorageHandler(std::string fileName){
		_fileName = fileName;
		loadFromSaveFile(_fileName);
	}

	std::vector<Task>& getAllTask() {
		return Tasks;
	}

	void add(Task task) {
		Tasks.push_back(task);
	}

};

#endif