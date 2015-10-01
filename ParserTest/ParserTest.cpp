#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest {
	TEST_CLASS(AddActivity) {
	public:

		TEST_METHOD(testExtractAddActivity) {
			std::string testUserInput = "add something FROM 2002-01-20 23:59:59.000 TO 2002-01-22 23:59:59.000";
			Parser parser;

			PrimaryCommandType expectedCommand = Add;
			std::string expectedTaskName = "something";
			boost::posix_time::ptime expectedStartDate(boost::posix_time::time_from_string("2002-01-20 23:59:59.000"));
			boost::posix_time::ptime expectedEndDate(boost::posix_time::time_from_string("2002-01-22 23:59:59.000"));

			CommandTokens output;
			output = parser.parse(testUserInput);

			Assert::AreEqual((int) expectedCommand, (int) output.getPrimaryCommand());
			Assert::IsTrue(boost::posix_time::to_simple_string(expectedStartDate) == boost::posix_time::to_simple_string(output.getStartDateTime()));
			Assert::IsTrue(boost::posix_time::to_simple_string(expectedEndDate) == boost::posix_time::to_simple_string(output.getEndDateTime()));
		}

		TEST_METHOD(testExtractDeleteFromTo) {
			std::string testUserInput = "DELETE FROM 2002-01-20 23:59:59.000 TO 2002-01-22 23:59:59.000";
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
	};
}