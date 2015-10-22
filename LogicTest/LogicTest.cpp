#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest {
	TEST_CLASS(CommandCreatorTest) {
public:

	TEST_METHOD(testCreateAddFloatCommand) {
		CommandCreator creator;

		CommandTokens token;

		//normal case
		token.setPrimaryCommand(CommandTokens::Add);
		token.setSecondaryCommand(CommandTokens::Floating);
		token.setTaskName(std::string("do something"));
		AddCommand* command = creator.testProcessAddCommand(token);
		Task task("do something");
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::PrimaryCommandType::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::SecondaryCommandType::Floating);
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(true, command->getTask() == task);

		//empty string case
		token.setTaskName(std::string(""));

		try {
			command = creator.testProcessAddCommand(token);
			Assert::AreEqual(false,true);  //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_EMPTY_TASK_TEXT.c_str(), e.what());
		}

		//String length = 150 which is character limit of task text.
		//Upper boundary of valid region.
		std::string testString = "                                                                                                                                                      ";
		token.setTaskName(testString);

		Assert::AreEqual((size_t)150, testString.size());

		command = creator.testProcessAddCommand(token);
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::PrimaryCommandType::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::SecondaryCommandType::Floating);
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(true, command->getTask() == Task(testString));

		//Smaller character no. that exceed character limit
		testString += " ";
		Assert::AreEqual((size_t)151, testString.size());

		token.setTaskName(testString);

		try {
			command = creator.testProcessAddCommand(token);
			Assert::AreEqual(false,true);  //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_LONG_TASK_TEXT.c_str(), e.what());
		}

	}

	TEST_METHOD(testCreateAddTodoCommand) {
		CommandCreator creator;
		CommandTokens token;

		//normal case
		std::string taskName = "do something";
		std::string timeString("2002-01-20 23:59:59.000");
		token.setPrimaryCommand(CommandTokens::Add);
		token.setSecondaryCommand(CommandTokens::Todo);
		token.setTaskName(taskName);
		token.setEndDateTime(boost::posix_time::time_from_string(timeString));

		AddCommand* command = creator.testProcessAddCommand(token);
		Task task("do something", boost::posix_time::time_from_string(timeString));
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::Todo);
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(true, command->getTask() == task);

		//empty string case
		token.setTaskName(std::string(""));

		try {
			command = creator.testProcessAddCommand(token);
			Assert::AreEqual(false,true);  //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_EMPTY_TASK_TEXT.c_str(), e.what());
		}

		//String length = 150 which is character limit of task text.
		//Upper boundary of valid region.
		std::string testString = "                                                                                                                                                      ";
		token.setTaskName(testString);

		Assert::AreEqual((size_t)150, testString.size());

		command = creator.testProcessAddCommand(token);
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::PrimaryCommandType::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::SecondaryCommandType::Todo);
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(true, command->getTask() == Task(testString, boost::posix_time::time_from_string(timeString)));

		//Smaller character no. that exceed character limit
		testString += " ";
		Assert::AreEqual((size_t)151, testString.size());

		token.setTaskName(testString);

		try {
			command = creator.testProcessAddCommand(token);
			Assert::AreEqual(false,true);  //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_LONG_TASK_TEXT.c_str(), e.what());
		}
	}

	TEST_METHOD(testCreateAddTimedCommand) {
		CommandCreator creator;
		CommandTokens token;

		//normal case
		std::string taskName = "do something";
		std::string timeString1("20-01-2002 23:59");
		std::string timeString2("20-02-2002 23:59");
		token.setPrimaryCommand(CommandTokens::Add);
		token.setSecondaryCommand(CommandTokens::Timed);
		token.setTaskName(taskName);
		token.setStartDateTime(boost::posix_time::time_from_string(timeString1));
		token.setEndDateTime(boost::posix_time::time_from_string(timeString2));

		AddCommand* command = creator.testProcessAddCommand(token);
		Task task("do something", boost::posix_time::time_from_string(timeString1), boost::posix_time::time_from_string(timeString2));
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::Timed);
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(true, command->getTask() == task);

		//empty string case
		token.setTaskName(std::string(""));

		try {
			command = creator.testProcessAddCommand(token);
			Assert::AreEqual(false,true);  //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_EMPTY_TASK_TEXT.c_str(), e.what());
		}

		//String length = 150 which is character limit of task text.
		//Upper boundary of valid region.
		std::string testString = "                                                                                                                                                      ";
		token.setTaskName(testString);

		Assert::AreEqual((size_t)150, testString.size());

		command = creator.testProcessAddCommand(token);
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::PrimaryCommandType::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::SecondaryCommandType::Timed);
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(true, command->getTask() == Task(testString, boost::posix_time::time_from_string(timeString1), boost::posix_time::time_from_string(timeString2)));

		//Smaller character no. that exceed character limit
		testString += " ";
		Assert::AreEqual((size_t)151, testString.size());

		token.setTaskName(testString);

		try {
			command = creator.testProcessAddCommand(token);
			Assert::AreEqual(false,true);  //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_LONG_TASK_TEXT.c_str(), e.what());
		}

		//boundary case where startDateTime is equals to endDateTime
		//still allowed
		token.setStartDateTime(boost::posix_time::time_from_string(timeString2));
		command = creator.testProcessAddCommand(token);
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::PrimaryCommandType::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::SecondaryCommandType::Timed);
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(true, command->getTask() == Task(testString, boost::posix_time::time_from_string(timeString2), boost::posix_time::time_from_string(timeString2)));

		//endDateTime is less than startDateTime
		//not allowed
		token.setEndDateTime(boost::posix_time::time_from_string(timeString1));
		try {
			command = creator.testProcessAddCommand(token);
			Assert::AreEqual(false, true); //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_END_LESS_THAN_START.c_str(), e.what());
		}

	}

	TEST_METHOD(testCreateDeleteIndexCommand) {
		CommandCreator creator;
		CommandTokens token;
		token.setPrimaryCommand(CommandTokens::Delete);
		token.setSecondaryCommand(CommandTokens::Index);

		DeleteIndexCommand* command;

		token.setIndex(1);
		command = creator.testProcessDeleteIndexCommand(token);
		Assert::AreEqual(true , CommandTokens::Delete==command->getPrimaryCommandType());
		Assert::AreEqual(true , CommandTokens::Index==command->getSecondaryCommandType());
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(size_t(1), command->getIndex());
	}
	};
}
