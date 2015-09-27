#pragma once

#include <string>
#include <vector>

class UIFeedback
{
public:
	UIFeedback(void);
	~UIFeedback(void);

	std::string results;
	std::vector< std::vector< std::string > > lines;
};

