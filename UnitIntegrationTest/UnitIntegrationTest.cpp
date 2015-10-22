// This project is the testing of the components working together
// The  catch blocks exist because logic may throw std::string exception or return normally
// TODO: pending working refresh commands to refresh list of tasks and check changes
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// All these const strings are declared because they are reused in multiple tests
const std::string FILEPATH = "defaultSaveFile.txt";

const std::string CMD_ADD = "AdD";
const std::string CMD_COMPLETE = "CoMpLeTe";
const std::string CMD_DELETE = "DeLeTe";
const std::string CMD_EDIT_NAME = "EdIt NaMe";
const std::string CMD_EDIT_START = "EdIt StArT";
const std::string CMD_EDIT_END = "EdIt EnD";
const std::string CMD_SEARCH = "SeArCh";
const std::string CMD_TAG = "TaG";
const std::string CMD_UNDO = "UnDo";
const std::string CMD_UNTAG = "UnTaG";
const std::string CMD_REFRESH = "refresh";

// Feedback 'ERROR' messages when Swiftask knows something is wrong and the command is not executed.
const std::string CMD_INVALID = "Invalid Command. No change is made.";
const std::string CMD_DUPLICATE = "Duplicate task is found. No change is made.";
const std::string UNKNOWN_EXCEPTION = "Unknown exception";
const std::string ONLY_POSITIVE = "Only positive index is allowed. No change is made.";
const std::string TASK_NOT_FOUND_AT = "No task is found at index ";

// These strings have spaces behind as a date is expected to be given.
const std::string BY = "By ";
const std::string FROM = "From ";
const std::string TO = "To ";

const std::string SPACE = " ";

const std::string TASK_A = "TASK A"; 
const std::string TASK_B = "TASK B";
const std::string TASK_C = "TASK C";
const std::string TASK_D = "TASK D";
const std::string TASK_E = "TASK E";
const std::string TASK_F = "TASK F";

const std::string NOT_A_DATE_TIME = "not-a-date-time";
const std::string DATE_TIME_1 = "2015-Oct-10 16:00:00";
const std::string DATE_TIME_2 = "2015-Oct-10 18:00:00";
const std::string DATE_TIME_3 = "2015-Oct-10 20:00:00";

const std::string TAG_A = "TAG A";
const std::string TAG_B = "TAG B";

// Valid add commands that will be used by test methods
const std::string addCommand1 = CMD_ADD + SPACE + TASK_A;
const std::string addCommand2 = CMD_ADD + SPACE + TASK_B + SPACE + BY + DATE_TIME_1;
const std::string addCommand3 = CMD_ADD + SPACE + TASK_C + SPACE + FROM + DATE_TIME_2 + SPACE + TO + DATE_TIME_3;


namespace UnitIntegrationTest {		
	TEST_CLASS(UnitIntegrationTest) {
public:
	TEST_METHOD(add) {
		// Important to do it here because logic keeps a copy of data on construction
		remove(FILEPATH.c_str());

		Logic logic;
		UIFeedback feedback;
		API::Task task;

		// Valid add commands
		// const std::string declared in the global scope

		// Invalid add commands
		// Not expecting to catch a bug

		// Testing add floating tasks in valid partition
		feedback = logic.executeCommand(addCommand1);
		task = feedback.getTasksForDisplay()[0];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreNotEqual(CMD_DUPLICATE, feedback.getFeedbackMessage());
		Assert::AreEqual(TASK_A, task.getTaskText());

		// Testing add tasks by deadline in valid partition
		feedback = logic.executeCommand(addCommand2);
		task = feedback.getTasksForDisplay()[1];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreNotEqual(CMD_DUPLICATE, feedback.getFeedbackMessage());
		Assert::AreEqual(TASK_B, task.getTaskText());
		Assert::AreEqual(DATE_TIME_1, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing add tasks with duration in valid partition
		feedback = logic.executeCommand(addCommand3);
		task = feedback.getTasksForDisplay()[2];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreNotEqual(CMD_DUPLICATE, feedback.getFeedbackMessage());
		Assert::AreEqual(TASK_C, task.getTaskText());
		Assert::AreEqual(DATE_TIME_2, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(DATE_TIME_3, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing add duplicates in invalid partition
		try {
			feedback = logic.executeCommand(addCommand1);
			Assert::AreEqual(CMD_DUPLICATE, feedback.getFeedbackMessage());

		} catch (std::string e) {
			Assert::AreEqual(CMD_DUPLICATE, e);
		}

		Assert::AreEqual((size_t) 3, feedback.getTasksForDisplay().size());
	}

	TEST_METHOD(refresh) {
		remove(FILEPATH.c_str());

		Logic logic;
		UIFeedback feedback;

		// Testing refresh at lower bound of valid parition
		feedback = logic.executeCommand(CMD_REFRESH);
		Assert::AreEqual((size_t) 0, feedback.getTasksForDisplay().size());

		feedback = logic.executeCommand(addCommand1);
		feedback = logic.executeCommand(addCommand2);
		feedback = logic.executeCommand(addCommand3);

		// Testing refresh in the valid partition when there are tasks
		feedback = logic.executeCommand(CMD_REFRESH);
		Assert::AreEqual((size_t) 3, feedback.getTasksForDisplay().size());
	}

	TEST_METHOD(edit) {
		remove(FILEPATH.c_str());

		Logic logic;
		UIFeedback feedback;
		API::Task task;

		// Valid edit commands
		std::string editCommand1 = CMD_EDIT_NAME + " 1 " + TASK_D;
		std::string editCommand2 = CMD_EDIT_END + " 2 " + DATE_TIME_3;
		std::string editCommand3 = CMD_EDIT_START + " 3 " + DATE_TIME_1;

		// Invalid edit commands
		std::string editCommand0 = CMD_EDIT_END + " 0 " + DATE_TIME_2;
		std::string editCommand4 = CMD_EDIT_START + " 4 " + DATE_TIME_1;

		feedback = logic.executeCommand(addCommand1);
		feedback = logic.executeCommand(addCommand2);
		feedback = logic.executeCommand(addCommand3);

		// Testing edit name and lower bound of valid partition
		feedback = logic.executeCommand(editCommand1);
		task = feedback.getTasksForDisplay()[0];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual(TASK_D, task.getTaskText());

		// Testing edit end date-time and in valid partition
		feedback = logic.executeCommand(editCommand2);
		task = feedback.getTasksForDisplay()[1];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual(DATE_TIME_3, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing edit start date-time and upper bound of valid partition
		feedback = logic.executeCommand(editCommand3);
		task = feedback.getTasksForDisplay()[2];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual(DATE_TIME_1, boost::posix_time::to_simple_string(task.getStartDateTime()));

		// Testing index upper bound of invalid partition that is smaller than valid partition
		try {
			feedback = logic.executeCommand(editCommand0);
			Assert::AreEqual(ONLY_POSITIVE, feedback.getFeedbackMessage());

		} catch (std::exception e) {
			Assert::AreEqual(ONLY_POSITIVE, std::string(e.what()));
		}

		feedback = logic.executeCommand(CMD_REFRESH);
		task = feedback.getTasksForDisplay()[0];
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing index lower bound of invalid partition that is larger than valid range partition
		try {
			feedback = logic.executeCommand(editCommand4);
			Assert::AreEqual(TASK_NOT_FOUND_AT + "4", feedback.getFeedbackMessage());

		} catch (std::string e) {
			Assert::AreEqual(TASK_NOT_FOUND_AT + "4", e);
		}

		feedback = logic.executeCommand(CMD_REFRESH);
		task = feedback.getTasksForDisplay()[2];
		Assert::AreEqual(DATE_TIME_1, boost::posix_time::to_simple_string(task.getStartDateTime()));

	}

	TEST_METHOD(tagUntag) {
		remove(FILEPATH.c_str());

		Logic logic;
		UIFeedback feedback;
		std::set<std::string> tags;

		// Testing tag/untag commands
		std::string tagCommand1 = CMD_TAG + " 1 " + TAG_A;
		std::string tagCommand1B = CMD_TAG + " 1 " + TAG_B;
		std::string tagCommand3 = CMD_TAG + " 3 " + TAG_A;
		std::string tagCommand0 = CMD_TAG + " 0 " + TAG_A;
		std::string tagCommand4 = CMD_TAG + " 4 " + TAG_A;

		std::string untagCommand1 = CMD_UNTAG + " 1 " + TAG_A;
		std::string untagCommand3 = CMD_UNTAG + " 3 " + TAG_A;
		std::string untagCommand0 = CMD_UNTAG + " 0 " + TAG_A;
		std::string untagCommand4 = CMD_UNTAG + " 4 " + TAG_A; 

		feedback = logic.executeCommand(addCommand1);
		feedback = logic.executeCommand(addCommand2);
		feedback = logic.executeCommand(addCommand3);

		// Tag Tests
		// Testing tag lower bound of valid partition
		feedback = logic.executeCommand(tagCommand1);
		tags = feedback.getTasksForDisplay()[0].getTags();

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 1, tags.size());
		Assert::AreEqual(TAG_A, *tags.begin());

		// Testing tag more than 1 tag
		feedback = logic.executeCommand(tagCommand1B);
		tags = feedback.getTasksForDisplay()[0].getTags();

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 2, tags.size());
		Assert::AreEqual(TAG_A, *tags.begin());
		Assert::AreEqual(TAG_B, *tags.end());

		// Testing tag upper bound of valid partition
		feedback = logic.executeCommand(tagCommand3);
		tags = feedback.getTasksForDisplay()[2].getTags();

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 1, tags.size());
		Assert::AreEqual(TAG_A, *tags.begin());

		// Testing tag upper bound of invalid partition that is smaller than valid partition
		try {
			feedback = logic.executeCommand(tagCommand0);
			Assert::AreEqual(ONLY_POSITIVE, feedback.getFeedbackMessage());

		} catch (std::exception e) {
			Assert::AreEqual(ONLY_POSITIVE, std::string(e.what()));
		}

		feedback = logic.executeCommand(CMD_REFRESH);
		tags = feedback.getTasksForDisplay()[0].getTags();

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 2, tags.size());
		Assert::AreEqual(TAG_A, *tags.begin());
		Assert::AreEqual(TAG_B, *tags.end());

		// Testing tag lower bound of invalid partition that is larger than valid partition
		try {
			feedback = logic.executeCommand(tagCommand4);
			Assert::AreEqual(TASK_NOT_FOUND_AT + "4", feedback.getFeedbackMessage());

		} catch (std::string e) {
			Assert::AreEqual(TASK_NOT_FOUND_AT + "4", e);
		}

		feedback = logic.executeCommand(CMD_REFRESH);
		tags = feedback.getTasksForDisplay()[2].getTags();

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 1, tags.size());
		Assert::AreEqual(TAG_A, *tags.begin());

		// Untag Tests
		// Testing untag lower bound of valid partition
		feedback = logic.executeCommand(untagCommand1);
		tags = feedback.getTasksForDisplay()[0].getTags();

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 1, tags.size());
		Assert::AreEqual(TAG_B, *tags.begin());

		// Testing untag upper bound of valid partition
		feedback = logic.executeCommand(untagCommand3);
		tags = feedback.getTasksForDisplay()[2].getTags();

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 0, tags.size());

		// Testing untag upper bound of invalid partition that is smaller than valid partition
		try {
			feedback = logic.executeCommand(untagCommand0);
			Assert::AreEqual(ONLY_POSITIVE, feedback.getFeedbackMessage());

		} catch (std::exception e) {
			Assert::AreEqual(ONLY_POSITIVE, std::string(e.what()));
		}

		feedback = logic.executeCommand(CMD_REFRESH);
		tags = feedback.getTasksForDisplay()[0].getTags();

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 1, tags.size());
		Assert::AreEqual(TAG_B, *tags.begin());

		// Testing untag lower bound of invalid partition that is larger than valid partition
		try {
			feedback = logic.executeCommand(tagCommand4);
			Assert::AreEqual(TASK_NOT_FOUND_AT + "4", feedback.getFeedbackMessage());

		} catch (std::string e) {
			Assert::AreEqual(TASK_NOT_FOUND_AT + "4", e);
		}

		feedback = logic.executeCommand(CMD_REFRESH);
		tags = feedback.getTasksForDisplay()[2].getTags();

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 0, tags.size());
	}

	TEST_METHOD(complete) {
		remove(FILEPATH.c_str());

		Logic logic;
		UIFeedback feedback;

		// Testing complete commands
		std::string completeCommand0 = CMD_COMPLETE + SPACE + "0";
		std::string completeCommand1 = CMD_COMPLETE + SPACE + "1";
		std::string completeCommand3 = CMD_COMPLETE + SPACE + "3";
		std::string completeCommand4 = CMD_COMPLETE + SPACE + "4";

		feedback = logic.executeCommand(addCommand1);
		feedback = logic.executeCommand(addCommand2);
		feedback = logic.executeCommand(addCommand3);

		// Testing complete lower bound of valid partition
		feedback = logic.executeCommand(completeCommand1);

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual(true, feedback.getTasksForDisplay()[0].isComplete());

		// Testing complete upper bound of valid partition
		feedback = logic.executeCommand(completeCommand3);

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual(true, feedback.getTasksForDisplay()[2].isComplete());

		// Testing complete upper bound of invalid partition that is smaller than valid partition
		try {
			feedback = logic.executeCommand(completeCommand0);
			Assert::AreEqual(ONLY_POSITIVE, feedback.getFeedbackMessage());

		} catch (std::exception e) {
			Assert::AreEqual(ONLY_POSITIVE, std::string(e.what()));
		}

		feedback = logic.executeCommand(CMD_REFRESH);
		Assert::AreEqual(true, feedback.getTasksForDisplay()[0].isComplete());

		// Testing complete lower bound of invalid partition that is larger than valid partition
		try {
			feedback = logic.executeCommand(completeCommand4);
			Assert::AreEqual(TASK_NOT_FOUND_AT + "4", feedback.getFeedbackMessage());

		} catch (std::string e) {
			Assert::AreEqual(TASK_NOT_FOUND_AT + "4", e);
		}

		feedback = logic.executeCommand(CMD_REFRESH);
		Assert::AreEqual(true, feedback.getTasksForDisplay()[2].isComplete());

	}

	// delete is a keyword hence deleteTasks
	TEST_METHOD(deleteTasks) {
		remove(FILEPATH.c_str());

		Logic logic;
		UIFeedback feedback;
		API::Task task;

		// Testing delete commands
		std::string deleteCommand0 = CMD_DELETE + SPACE + "0";
		std::string deleteCommand1 = CMD_DELETE + SPACE + "1";
		std::string deleteCommand2 = CMD_DELETE + SPACE + "2";

		feedback = logic.executeCommand(addCommand1);
		feedback = logic.executeCommand(addCommand2);
		feedback = logic.executeCommand(addCommand3);

		// Testing delete task within valid parition
		// May be trivial but leads to testing of deleting only one task
		feedback = logic.executeCommand(deleteCommand2);
		task = feedback.getTasksForDisplay()[1];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 2, feedback.getTasksForDisplay().size());
		Assert::AreEqual(TASK_C, task.getTaskText());
		Assert::AreEqual(DATE_TIME_2, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(DATE_TIME_3, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing delete upper bound of valid partition
		feedback = logic.executeCommand(deleteCommand2);
		task = feedback.getTasksForDisplay()[0];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 1, feedback.getTasksForDisplay().size());
		Assert::AreEqual(TASK_A, task.getTaskText());
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing index lower bound of invalid partition that is larger than valid partition
		try {
			feedback = logic.executeCommand(deleteCommand2);
			Assert::AreEqual(TASK_NOT_FOUND_AT + "2", feedback.getFeedbackMessage());

		} catch (std::string e) {
			Assert::AreEqual(TASK_NOT_FOUND_AT + "2", e);
		}

		feedback = logic.executeCommand(CMD_REFRESH);
		task = feedback.getTasksForDisplay()[0];
		Assert::AreEqual((size_t) 1, feedback.getTasksForDisplay().size());
		Assert::AreEqual(TASK_A, task.getTaskText());
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing index upper bound of invalid partition that is smaller than valid partition
		try {
			feedback = logic.executeCommand(deleteCommand0);
			Assert::AreEqual(ONLY_POSITIVE, feedback.getFeedbackMessage());

		} catch (std::exception e) {
			Assert::AreEqual(ONLY_POSITIVE, std::string(e.what()));
		}

		feedback = logic.executeCommand(CMD_REFRESH);
		Assert::AreEqual((size_t) 1, feedback.getTasksForDisplay().size());
		Assert::AreEqual(TASK_A, task.getTaskText());
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing delete lower bound of valid partition and delete only task
		feedback = logic.executeCommand(deleteCommand1);

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 0, feedback.getTasksForDisplay().size());

		// Not worth testing deleting empty because it is part of the invalid partitions
	}

	TEST_METHOD(dateTimeFormat) {
		// Important to do it here because logic keeps a copy of data on construction
		remove(FILEPATH.c_str());

		// Tests flexible formats
		// yyyy-mmm-dd hh:mm
		// dd-mm-yyyy hhmm
		std::string command1 = CMD_ADD + SPACE + TASK_A + SPACE + FROM + "2015-10-10 16:00" + SPACE + TO + "10-10-2015 1800";

		Logic logic;
		UIFeedback feedback;
		API::Task task;

		feedback = logic.executeCommand(command1);
		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 1, feedback.getTasksForDisplay().size());
		task = feedback.getTasksForDisplay()[0];

		Assert::AreEqual(DATE_TIME_1, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(DATE_TIME_2, boost::posix_time::to_simple_string(task.getEndDateTime()));
	}
	// TODO: Below

	// Testing flexible inputs like variation of date-time

	// Testing limits of input, number of tasks etc.

	// Testing more complex permutation of commands; combining multiple inputs.
	};
}