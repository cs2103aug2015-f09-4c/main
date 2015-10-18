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
const std::string CMD_UNDO = "UnDo";

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

namespace UnitIntegrationTest {		
	TEST_CLASS(UnitIntegrationTest) {
public:
	TEST_METHOD(integration_Commands_AddEditCompleteDelete) {
		// Important to do it here because logic keeps a copy of data on construction
		remove(FILEPATH.c_str());

		Logic logic;
		UIFeedback feedback;
		API::Task task;
		std::string errorMessage = CMD_INVALID;	// Logic only throws std::string CMD_INVALID messages

		// Testing add commands
		// Valid commands
		std::string addCommand1 = CMD_ADD + SPACE + TASK_A;
		std::string addCommand2 = CMD_ADD + SPACE + TASK_B + SPACE + BY + DATE_TIME_1;
		std::string addCommand3 = CMD_ADD + SPACE + TASK_C + SPACE + FROM + DATE_TIME_2 + SPACE + TO + DATE_TIME_3;

		// Invalid commands
		// Not expecting to catch a bug

		// Testing add floating tasks
		feedback = logic.executeCommand(addCommand1);
		task = feedback.getTasksForDisplay()[0];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreNotEqual(CMD_DUPLICATE, feedback.getFeedbackMessage());
		Assert::AreEqual(TASK_A, task.getTaskText());

		// Testing add tasks by deadline
		feedback = logic.executeCommand(addCommand2);
		task = feedback.getTasksForDisplay()[1];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreNotEqual(CMD_DUPLICATE, feedback.getFeedbackMessage());
		Assert::AreEqual(TASK_B, task.getTaskText());
		Assert::AreEqual(DATE_TIME_1, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing add tasks with duration
		feedback = logic.executeCommand(addCommand3);
		task = feedback.getTasksForDisplay()[2];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreNotEqual(CMD_DUPLICATE, feedback.getFeedbackMessage());
		Assert::AreEqual(TASK_C, task.getTaskText());
		Assert::AreEqual(DATE_TIME_2, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(DATE_TIME_3, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing add duplicates
		feedback = logic.executeCommand(addCommand1);

		Assert::AreEqual(CMD_DUPLICATE, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 3, feedback.getTasksForDisplay().size());

		// Expected status of the tasks in taskText, startDateTime, endDateTime, complete:
		// TASK_A, NOT_A_DATE_TIME, NOT_A_DATE_TIME, 0
		// TASK_B, NOT_A_DATE_TIME, DATE_TIME_1, 0
		// TASK_C, DATE_TIME_2, DATE_TIME_3, 0

		// Testing edit commands
		// Valid commands
		std::string editCommand1 = CMD_EDIT_NAME + SPACE + "1" + SPACE + TASK_D;
		std::string editCommand2 = CMD_EDIT_END + SPACE + "2" + SPACE + DATE_TIME_3;
		std::string editCommand3 = CMD_EDIT_START + SPACE + "3" + SPACE + DATE_TIME_1;

		// Invalid commands
		std::string editCommand0 = CMD_EDIT_END + SPACE + "0" + SPACE + DATE_TIME_2;
		std::string editCommand4 = CMD_EDIT_START + SPACE + "4" + SPACE + DATE_TIME_1;

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

		// Testing index lower bound of invalid partition that is larger than valid range partition
		feedback = logic.executeCommand(editCommand0);
		task = feedback.getTasksForDisplay()[0];

		Assert::AreEqual(ONLY_POSITIVE, feedback.getFeedbackMessage());
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing index upper bound of invalid partition that is smaller than valid partition
		feedback = logic.executeCommand(editCommand4);
		task = feedback.getTasksForDisplay()[2];

		Assert::AreEqual(TASK_NOT_FOUND_AT + "4", feedback.getFeedbackMessage());
		Assert::AreEqual(DATE_TIME_1, boost::posix_time::to_simple_string(task.getStartDateTime()));

		// Expected status of the tasks in taskText, startDateTime, endDateTime, complete:
		// TASK_D, NOT_A_DATE_TIME, NOT_A_DATE_TIME, 0
		// TASK_B, NOT_A_DATE_TIME, DATE_TIME_3, 0
		// TASK_C, DATE_TIME_1, DATE_TIME_3, 0

		// Testing complete commands
		std::string completeCommand0 = CMD_COMPLETE + SPACE + "0";
		std::string completeCommand1 = CMD_COMPLETE + SPACE + "1";
		std::string completeCommand3 = CMD_COMPLETE + SPACE + "3";
		std::string completeCommand4 = CMD_COMPLETE + SPACE + "4";

		// Testing complete lower bound of valid partition
		feedback = logic.executeCommand(completeCommand1);

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual(true, feedback.getTasksForDisplay()[0].isComplete());

		// Testing complete upper bound of valid partition
		feedback = logic.executeCommand(completeCommand3);

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual(true, feedback.getTasksForDisplay()[2].isComplete());

		// Testing complete upper bound of invalid partition that is smaller than valid partition
		feedback = logic.executeCommand(completeCommand0);

		Assert::AreEqual(ONLY_POSITIVE, feedback.getFeedbackMessage());
		Assert::AreEqual(true, feedback.getTasksForDisplay()[0].isComplete());

		// Testing complete lower bound of invalid partition that is larger than valid partition
		feedback = logic.executeCommand(completeCommand4);

		Assert::AreEqual(TASK_NOT_FOUND_AT + "4", feedback.getFeedbackMessage());
		Assert::AreEqual(true, feedback.getTasksForDisplay()[2].isComplete());

		// Expected status of the tasks in taskText, startDateTime, endDateTime, complete:
		// TASK_D, NOT_A_DATE_TIME, NOT_A_DATE_TIME, 1
		// TASK_B, NOT_A_DATE_TIME, DATE_TIME_3, 0
		// TASK_C, DATE_TIME_1, DATE_TIME_3, 1

		// Testing delete commands
		std::string deleteCommand0 = CMD_DELETE + SPACE + "0";
		std::string deleteCommand1 = CMD_DELETE + SPACE + "1";
		std::string deleteCommand2 = CMD_DELETE + SPACE + "2";

		// Testing delete task within valid parition
		// May be trivial but leads to testing of deleting only one task
		feedback = logic.executeCommand(deleteCommand2);
		task = feedback.getTasksForDisplay()[1];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 2, feedback.getTasksForDisplay().size());
		Assert::AreEqual(TASK_C, task.getTaskText());
		Assert::AreEqual(DATE_TIME_1, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(DATE_TIME_3, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing delete upper bound of valid partition
		feedback = logic.executeCommand(deleteCommand2);
		task = feedback.getTasksForDisplay()[0];

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 1, feedback.getTasksForDisplay().size());
		Assert::AreEqual(TASK_D, task.getTaskText());
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing index lower bound of invalid partition that is larger than valid partition
		feedback = logic.executeCommand(deleteCommand2);
		task = feedback.getTasksForDisplay()[0];

		Assert::AreEqual(TASK_NOT_FOUND_AT + "2", feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 1, feedback.getTasksForDisplay().size());
		Assert::AreEqual(TASK_D, task.getTaskText());
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing index upper bound of invalid partition that is smaller than valid partition
		feedback = logic.executeCommand(deleteCommand0);

		Assert::AreEqual(ONLY_POSITIVE, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 1, feedback.getTasksForDisplay().size());
		Assert::AreEqual(TASK_D, task.getTaskText());
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getStartDateTime()));
		Assert::AreEqual(NOT_A_DATE_TIME, boost::posix_time::to_simple_string(task.getEndDateTime()));

		// Testing delete lower bound of valid partition and delete only task
		feedback = logic.executeCommand(deleteCommand1);

		Assert::AreNotEqual(CMD_INVALID, feedback.getFeedbackMessage());
		Assert::AreEqual((size_t) 0, feedback.getTasksForDisplay().size());

		// Not worth testing deleting empty because it is part of the invalid partitions

		// TODO: Below

		// Testing flexible inputs like variation of date-time

		// Testing limits of input, number of tasks etc.

		// Testing more complex permutation of commands; combining multiple inputs.
	}
	};
}