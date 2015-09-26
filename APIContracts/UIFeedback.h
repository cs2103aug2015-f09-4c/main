#pragma once

#include <vector>
#include "Task.h"

class UIFeedback{
private:
	std::vector<Task> _tasksForDisplay;
	std::string _feedbackMessage;
public:
	UIFeedback(std::vector<Task>& tasksForDisplay, std::string feedbackMessage);

	std::vector<Task>& getTasksForDisplay();
	std::string getFeedbackMessage();
};

