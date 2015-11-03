//@@author A0112218W

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
		std::string testString = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
		token.setTaskName(testString);

		Assert::AreEqual((size_t)128, testString.size());

		command = creator.testProcessAddCommand(token);
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::PrimaryCommandType::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::SecondaryCommandType::Floating);
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(true, command->getTask() == Task(testString));

		//Smaller character no. that exceed character limit
		testString += "1";
		Assert::AreEqual((size_t)129, testString.size());

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
		token.setSecondaryCommand(CommandTokens::By);
		token.setTaskName(taskName);
		token.setEndDateTime(boost::posix_time::time_from_string(timeString));

		AddCommand* command = creator.testProcessAddCommand(token);
		Task task("do something", boost::posix_time::time_from_string(timeString));
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::By);
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
		std::string testString = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
		token.setTaskName(testString);

		Assert::AreEqual((size_t)128, testString.size());

		command = creator.testProcessAddCommand(token);
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::PrimaryCommandType::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::SecondaryCommandType::By);
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(true, command->getTask() == Task(testString, boost::posix_time::time_from_string(timeString)));

		//Smaller character no. that exceed character limit
		testString += "1";
		Assert::AreEqual((size_t)129, testString.size());

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
		std::string timeString1("2002-01-20 23:59:59");
		std::string timeString2("2002-01-21 23:59:59");
		token.setPrimaryCommand(CommandTokens::Add);
		token.setSecondaryCommand(CommandTokens::FromTo);
		token.setTaskName(taskName);
		token.setStartDateTime(boost::posix_time::time_from_string(timeString1));
		token.setEndDateTime(boost::posix_time::time_from_string(timeString2));

		AddCommand* command = creator.testProcessAddCommand(token);
		Task task("do something", boost::posix_time::time_from_string(timeString1), boost::posix_time::time_from_string(timeString2));
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::FromTo);
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
		std::string testString = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111";
		token.setTaskName(testString);

		Assert::AreEqual((size_t)128, testString.size());

		command = creator.testProcessAddCommand(token);
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::PrimaryCommandType::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::SecondaryCommandType::FromTo);
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(true, command->getTask() == Task(testString, boost::posix_time::time_from_string(timeString1), boost::posix_time::time_from_string(timeString2)));

		//Smaller character no. that exceed character limit
		testString += "1";
		Assert::AreEqual((size_t)129, testString.size());

		token.setTaskName(testString);

		try {
			command = creator.testProcessAddCommand(token);
			Assert::AreEqual(false,true);  //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_LONG_TASK_TEXT.c_str(), e.what());
		}

		//boundary case where startDateTime is equals to endDateTime
		//still allowed
		testString = testString.substr(0,128);
		token.setTaskName(testString);
		token.setStartDateTime(boost::posix_time::time_from_string(timeString2));
		
		command = creator.testProcessAddCommand(token);
		Assert::AreEqual(true, command->getPrimaryCommandType() == CommandTokens::PrimaryCommandType::Add);
		Assert::AreEqual(true, command->getSecondaryCommandType() == CommandTokens::SecondaryCommandType::FromTo);
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

		//Invalid case
		token.setIndex(0);
		try {
			command = creator.testProcessDeleteIndexCommand(token);
			Assert::AreEqual(false,true); //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_NON_POSITIVE_INDEX.c_str(), e.what());
		}
	}

	TEST_METHOD(testCreateDeleteBeforeCommand) {
		CommandCreator creator;
		CommandTokens token;
		token.setPrimaryCommand(CommandTokens::Delete);
		token.setSecondaryCommand(CommandTokens::By);

		DeleteBeforeCommand* command = NULL;

		std::string timeString("2002-01-20 23:59:59");
		std::string expectedString("2002-Jan-20 23:59:59");
		boost::posix_time::ptime endTime = boost::posix_time::time_from_string(timeString);

		token.setEndDateTime(endTime);
		command = creator.testProcessDeleteBeforeCommand(token);
		Assert::AreEqual(true , CommandTokens::Delete==command->getPrimaryCommandType());
		Assert::AreEqual(true , CommandTokens::By==command->getSecondaryCommandType());
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(expectedString.c_str(), boost::posix_time::to_simple_string(command->getEndDateTime()).c_str());

		token.setEndDateTime(boost::posix_time::ptime());
		try {
			command = creator.testProcessDeleteBeforeCommand(token);
			Assert::AreEqual(false, true); //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_INVALID_DATE_TIME.c_str(), e.what());
		}
	}

	TEST_METHOD(testCreateDeleteFromToCommand) {
		CommandCreator creator;
		CommandTokens token;
		token.setPrimaryCommand(CommandTokens::Delete);
		token.setSecondaryCommand(CommandTokens::FromTo);

		DeleteFromToCommand* command = NULL;

		std::string timeString1("2002-01-20 23:59:59");
		std::string timeString2("2002-01-21 23:59:59");
		std::string expectedString1("2002-Jan-20 23:59:59");
		std::string expectedString2("2002-Jan-21 23:59:59");
		boost::posix_time::ptime startTime = boost::posix_time::time_from_string(timeString1);
		boost::posix_time::ptime endTime = boost::posix_time::time_from_string(timeString2);

		token.setStartDateTime(startTime);
		token.setEndDateTime(endTime);
		command = creator.testProcessDeleteFromToCommand(token);
		Assert::AreEqual(true , CommandTokens::Delete==command->getPrimaryCommandType());
		Assert::AreEqual(true , CommandTokens::FromTo==command->getSecondaryCommandType());
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());
		Assert::AreEqual(expectedString1.c_str(), boost::posix_time::to_simple_string(command->getStartDateTime()).c_str());
		Assert::AreEqual(expectedString2.c_str(), boost::posix_time::to_simple_string(command->getEndDateTime()).c_str());

		//startTime cannot be more than endTime, thus exception should be thrown.
		token.setEndDateTime(startTime);
		token.setStartDateTime(endTime);
		try {
			command = creator.testProcessDeleteFromToCommand(token);
			Assert::AreEqual(false, true); //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_END_LESS_THAN_START.c_str(), e.what());
		}

		//endDateTime is not a date time, exception should be thrown.
		token.setStartDateTime(startTime);
		token.setEndDateTime(boost::posix_time::ptime());
		try {
			command = creator.testProcessDeleteFromToCommand(token);
			Assert::AreEqual(false, true); //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_INVALID_DATE_TIME.c_str(), e.what());
		}

		//startDateTime is not a date time, exception should be thrown.
		token.setStartDateTime(boost::posix_time::ptime());
		token.setEndDateTime(endTime);
		try {
			command = creator.testProcessDeleteFromToCommand(token);
			Assert::AreEqual(false, true); //expect exception thrown to skip this line.
		} catch (std::exception e) {
			Assert::AreEqual(MESSAGE_INVALID_DATE_TIME.c_str(), e.what());
		}
	}

	TEST_METHOD (testCreateDeleteAllCommand) {
		CommandCreator creator;
		CommandTokens token;
		token.setPrimaryCommand(CommandTokens::Delete);
		token.setSecondaryCommand(CommandTokens::All);

		DeleteAllCommand* command = NULL;

		command = creator.testProcessDeleteAllCommand(token);
		Assert::AreEqual(true , CommandTokens::Delete==command->getPrimaryCommandType());
		Assert::AreEqual(true , CommandTokens::All==command->getSecondaryCommandType());
		Assert::AreEqual(false, command->isExecuted());
		Assert::AreEqual(true, command->isValid());		
	}
	};
}
