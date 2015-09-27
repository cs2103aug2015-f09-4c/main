#pragma once

#include <string>
#include "UIFeedback.h"

class Logic
{
public:
	Logic(void);
	~Logic(void);

	UIFeedback executeCommand(std::string aString);
};

