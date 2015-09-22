#pragma once
#include <string>
#include <vector>

class Feedback {
public:
	std::string results;
	std::vector<std::vector<std::string> > lines;
public:
	Feedback() {
		results = "";
		std::vector<std::string> testlines;

		testlines.push_back("Test");
		testlines.push_back("has");
		testlines.push_back("passed");
		testlines.push_back("!");

		lines.push_back(testlines);
	}
	~Feedback() {
	}
};

class Logic {
public:
	Logic(void);
	~Logic(void);

	Feedback executeCommand(std::string userInput);
};

