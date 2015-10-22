#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "../Logic/Task.h"
#include "../boost/date_time/posix_time/posix_time.hpp"

const std::string defaultPath = "defaultSaveFile.txt";

class PhysicalStorageHandler
{
public:
	PhysicalStorageHandler();
	void saveToFile(std::vector<API::Task>&, std::string = defaultPath);
	void loadFromFile(std::vector<API::Task>&, std::string = defaultPath);
	virtual ~PhysicalStorageHandler(void);
};

