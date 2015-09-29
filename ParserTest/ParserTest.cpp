#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Parser/Parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest
{
	TEST_CLASS(AddActivity)
	{
	public:

		TEST_METHOD(TestExtractAdd)
		{
			std::string testUserInput = "add something FROM 2002-01-20 23:59:59.000 TO 2002-01-22 23:59:59.000";
			Parser parser;

			PrimaryCommandType expectedCommand = Add;
			std::string expectedTaskName = "something";
			boost::posix_time::ptime expectedStartDate(boost::posix_time::time_from_string("2002-01-20 23:59:59.000"));
			boost::posix_time::ptime expectedEndDate(boost::posix_time::time_from_string("2002-01-22 23:59:59.000"));

			CommandTokens output;
			output = parser.parse(testUserInput);

			Assert::AreEqual((int) expectedCommand, (int) output.getPrimaryCommand());
			Assert::AreEqual(expectedTaskName, output.getTaskName());
			Assert::IsTrue(boost::posix_time::to_simple_string(expectedStartDate) == boost::posix_time::to_simple_string(output.getStartDateTime()));
			Assert::IsTrue(boost::posix_time::to_simple_string(expectedEndDate) == boost::posix_time::to_simple_string(output.getEndDateTime()));
		}

	};
}