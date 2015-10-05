#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest {
	TEST_CLASS(ParserTester) {
	public:
		CommandTokens _expected, _actual;
		Parser _parser;
		std::string _testUserInput;

		TEST_METHOD(testTokeniseAddActivityCommand) {
			_testUserInput = "add activityTask FROM 2002-01-20 23:59:59.000 to 2002-01-22 23:59:59.000";
			_actual = _parser.parse(_testUserInput);

			_expected.setPrimaryCommand(PrimaryCommandType::Add);
			_expected.setSecondaryCommand(SecondaryCommandType::Timed);
			_expected.setTaskName("activityTask");

			std::vector< std::string > expectedDetails;
			expectedDetails.push_back("activityTask");
			_expected.setDetails(expectedDetails);

			boost::posix_time::ptime expectedStartDate(boost::posix_time::time_from_string("2002-01-20 23:59:59.000"));
			boost::posix_time::ptime expectedEndDate(boost::posix_time::time_from_string("2002-01-22 23:59:59.000"));
			_expected.setStartDateTime(expectedStartDate);
			_expected.setEndDateTime(expectedEndDate);

			compareCommandTokens(_expected, _actual);
		}

		TEST_METHOD(testTokeniseAddTodoCommand) {
			_testUserInput = "add todoTask by 2002-01-22 23:59:59.000";
			_actual = _parser.parse(_testUserInput);

			_expected.setPrimaryCommand(PrimaryCommandType::Add);
			_expected.setSecondaryCommand(SecondaryCommandType::Todo);
			_expected.setTaskName("todoTask");

			std::vector< std::string > expectedDetails;
			expectedDetails.push_back("todoTask");
			_expected.setDetails(expectedDetails);

			boost::posix_time::ptime expectedEndDate(boost::posix_time::time_from_string("2002-01-22 23:59:59.000"));
			_expected.setEndDateTime(expectedEndDate);

			compareCommandTokens(_expected, _actual);
		}

		TEST_METHOD(testTokeniseAddFloatingCommand) {
			_testUserInput = "add floatingTask";
			_actual = _parser.parse(_testUserInput);

			_expected.setPrimaryCommand(PrimaryCommandType::Add);
			_expected.setSecondaryCommand(SecondaryCommandType::Floating);
			_expected.setTaskName("floatingTask");

			std::vector< std::string > expectedDetails;
			expectedDetails.push_back("floatingTask");
			_expected.setDetails(expectedDetails);

			compareCommandTokens(_expected, _actual);
		}

		TEST_METHOD(testTokeniseDelete) {
			std::string testUserInput = "delete from 2002-01-20 23:59:59.000 to 2002-01-22 23:59:59.000";
			Parser parser;

			PrimaryCommandType expectedCommand = Delete;
			boost::posix_time::ptime expectedStartDate(boost::posix_time::time_from_string("2002-01-20 23:59:59.000"));
			boost::posix_time::ptime expectedEndDate(boost::posix_time::time_from_string("2002-01-22 23:59:59.000"));

			CommandTokens output;
			output = parser.parse(testUserInput);

			Assert::AreEqual((int) expectedCommand, (int) output.getPrimaryCommand());
			Assert::IsTrue(boost::posix_time::to_simple_string(expectedStartDate) == boost::posix_time::to_simple_string(output.getStartDateTime()));
			Assert::IsTrue(boost::posix_time::to_simple_string(expectedEndDate) == boost::posix_time::to_simple_string(output.getEndDateTime()));
		}

		TEST_METHOD(testTokeniseDisplay) {

		}

		void compareCommandTokens(CommandTokens expected, CommandTokens actual) {
			Assert::AreEqual(int (expected.getPrimaryCommand()), int (actual.getPrimaryCommand()));
			Assert::AreEqual(int (expected.getSecondaryCommand()), int (actual.getSecondaryCommand()));
			Assert::AreEqual(expected.getTaskName(), actual.getTaskName());
			Assert::IsTrue(expected.getStartDateTime() == actual.getStartDateTime());
			Assert::IsTrue(expected.getEndDateTime() == actual.getEndDateTime());
			Assert::AreEqual(expected.getIndex(), actual.getIndex());

			std::vector< std::string > expectedDetails, actualDetails;
			expectedDetails = expected.getDetails();
			actualDetails = actual.getDetails();

			Assert::AreEqual(expectedDetails.empty(), actualDetails.empty());

			if (!expectedDetails.empty()) {
				for (unsigned i = 0; i < expectedDetails.size(); i++) {
					Assert::AreEqual(expectedDetails.at(i), actualDetails.at(i));
				}
			}
		}
	};
}