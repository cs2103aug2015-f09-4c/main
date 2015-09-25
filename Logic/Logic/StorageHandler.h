#include <fstream>
#include "..\..\Swiftask.h"
#include "Logic.h"

class StorageHandler {
private:
	std::vector<Task> Tasks;
	std::string _fileName;

	static void loadFromSaveFie(string fileName) {
		std::ifstream loadFile(fileName);
		if (loadFile.is_open()) {
			while (!loadFile.eof())
			{
				std::string task = loadFile.getline();
				std::string startDateTimeString = loadFile.getline();
				std::string endDateTimeString = loadFile.getline();

			}
		}
	}


public:
	StorageHandler(){
		loadFromSaveFile()


	}

};