#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{		
	TEST_CLASS(CommandCreatorTest)
	{
	public:
		
		TEST_METHOD(TestCreateAddFloatCommand)
		{
			CommandCreator creator;
			std::vector<std::string> details;
			details.push_back(std::string("do something"));
			CommandTokens token1(Add,Floating,details);
			AddCommand* command = creator.testProcessAddCommand(token1);
			Task task("do something");
			Assert::AreEqual(true, command->getPrimaryCommandType()==Add);
			Assert::AreEqual(true, command->getSecondaryCommandType()==Floating);
			Assert::AreEqual(false, command->isExecutedSuccessfully());
			Assert::AreEqual(true, command->isValid());
			Assert::AreEqual(true, command->getTask() == task);
		}

		TEST_METHOD(TestCreateAddTodoCommand)
		{
			CommandCreator creator;
			std::vector<std::string> details;
			details.push_back(std::string("do something"));
			std::string timeString("2002-01-20 23:59:59.000");
			CommandTokens token1(Add,Todo,details, boost::posix_time::time_from_string(timeString));
			AddCommand* command = creator.testProcessAddCommand(token1);
			Task task("do something",boost::posix_time::time_from_string(timeString));
			Assert::AreEqual(true, command->getPrimaryCommandType()==Add);
			Assert::AreEqual(true, command->getSecondaryCommandType()==Todo);
			Assert::AreEqual(false, command->isExecutedSuccessfully());
			Assert::AreEqual(true, command->isValid());
			Assert::AreEqual(true, command->getTask() == task);
		}

		TEST_METHOD(TestCreateAddTimedCommand)
		{
			CommandCreator creator;
			std::vector<std::string> details;
			details.push_back(std::string("do something"));
			std::string timeString1("2002-01-20 23:59:59.000");
			std::string timeString2("2002-01-21 23:59:59.000");
			CommandTokens token1(Add,Timed,details, boost::posix_time::time_from_string(timeString1), boost::posix_time::time_from_string(timeString2));
			AddCommand* command = creator.testProcessAddCommand(token1);
			Task task("do something",boost::posix_time::time_from_string(timeString1),boost::posix_time::time_from_string(timeString2));
			Assert::AreEqual(true, command->getPrimaryCommandType()==Add);
			Assert::AreEqual(true, command->getSecondaryCommandType()==Timed);
			Assert::AreEqual(false, command->isExecutedSuccessfully());
			Assert::AreEqual(true, command->isValid());
			Assert::AreEqual(true, command->getTask() == task);
		}

	};
}