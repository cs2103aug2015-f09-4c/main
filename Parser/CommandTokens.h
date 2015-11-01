//@@ author A0097681N
#pragma once
#include <exception>
#include <vector>
#include "boost\date_time\posix_time\ptime.hpp"

class CommandTokens {
public:
	// Command Type for main groups of operation
	enum PrimaryCommandType {
		Invalid,

		// administrative commands
		Help,
		Configure,
		Refresh,
		Undo,

		// task management commands
		Add, Display, Edit, Delete,
		Search,	Sort,
		Tag, Untag,
		MarkAsComplete,
		Export,	Import
	};

	// Command Type to further specify the operation
	enum SecondaryCommandType {
		None,

		// general task filters
		All, Index,
		FromTo, By,	Floating,
		Completed,
		Name, Start, End,
		Tags,

		// specific task filters
		EndAfter,EndBefore,
		StartAfter,	StartBefore,

		// miscellaneous
		SaveLocation
	};

	CommandTokens(PrimaryCommandType primaryCommandType = Invalid,
	              SecondaryCommandType secondaryCommandType = None,
	              std::string taskName = "",
	              boost::posix_time::ptime startDateTime = boost::posix_time::ptime(),
	              boost::posix_time::ptime endDateTime = boost::posix_time::ptime(),
	              std::vector<std::string> tags = std::vector<std::string>(0),
	              int index = -1);

	bool isValid();
	void reset();

	PrimaryCommandType getPrimaryCommand();
	SecondaryCommandType getSecondaryCommand();
	std::string getTaskName();
	std::vector<std::string>& getTags();
	boost::posix_time::ptime getStartDateTime();
	boost::posix_time::ptime getEndDateTime();
	int getIndex();
	std::string getOtherCommandParameter();

	void setPrimaryCommand(PrimaryCommandType newPrimaryCommand);
	void setSecondaryCommand(SecondaryCommandType newSecondaryCommand);
	void setTaskName(std::string newTaskName);
	void setTags(std::vector<std::string> newTags);
	void setStartDateTime(boost::posix_time::ptime newStartDateTime);
	void setEndDateTime(boost::posix_time::ptime newEndDateTime);
	void setIndex(int newIndex);
	void setOtherCommandParameter(std::string newOtherCommandParameter);

private:
	PrimaryCommandType _primaryCommandType;
	SecondaryCommandType _secondaryCommandType;
	std::string _taskName;
	boost::posix_time::ptime _startDateTime;
	boost::posix_time::ptime _endDateTime;
	std::vector<std::string> _tags;
	int _index;
	std::string _otherCommandParameter;
};

class CommandDoesNotExistException: public std::exception {
public:
	virtual const char* what() const throw() override {
		return "Command does not exist";
	}
};
