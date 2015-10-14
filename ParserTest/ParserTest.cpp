#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest {
	TEST_CLASS(ParserTester) {
		public:
		Parser _parser;

		TEST_METHOD(testTokeniseAddActivityCommand) {
			std::string testUserInput = "ADD activityTask FROM 2002-01-20 23:59:59.000 TO 2002-01-22 23:59:59.000";
			CommandTokens actual, expected;

			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(PrimaryCommandType::Add,
			                                      SecondaryCommandType::Timed,
			                                      "activityTask",
			                                      "2002-01-20 23:59:59.000",
			                                      "2002-01-22 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseAddTodoCommand) {
			std::string testUserInput = "ADD todoTask BY 2002-01-22 23:59:59.000";
			CommandTokens actual, expected;

			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(PrimaryCommandType::Add,
			                                      SecondaryCommandType::Todo,
			                                      "todoTask",
			                                      "",
			                                      "2002-01-22 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseAddFloatingCommand) {
			std::string testUserInput = "ADD floatingTask";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(PrimaryCommandType::Add,
			                                      SecondaryCommandType::Floating,
			                                      "floatingTask",
			                                      "",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseDeleteFromTo) {
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

		TEST_METHOD(testTokeniseDeleteFrom) {
		}

		TEST_METHOD(testTokeniseDeleteAll) {
		}

		TEST_METHOD(testTokeniseDeleteBy) {
		}

		TEST_METHOD(testTokeniseDeleteIndex) {
		}

		TEST_METHOD(testTokeniseDisplayBy) {
		}

		TEST_METHOD(testTokeniseDisplayFrom) {
		}

		TEST_METHOD(testTokeniseDisplayAll) {
		}

		TEST_METHOD(testTokeniseDisplayFloating) {
		}

		TEST_METHOD(testTokeniseEditNameCommand) {
		}

		TEST_METHOD(testTokeniseEditStartDateCommand) {
		}

		TEST_METHOD(testTokeniseEditEndDateCommand) {
		}

		TEST_METHOD(testTokeniseCompleteCommand) {
		}

		TEST_METHOD(testDateParser) {
		}

		CommandTokens buildExpectedCommandTokens(PrimaryCommandType primaryCommandType,
		                                         SecondaryCommandType secondaryCommandType,
		                                         std::string taskName,
		                                         std::string startDate,
		                                         std::string endDate,
		                                         int index) {

			CommandTokens expected;

			expected.setPrimaryCommand(primaryCommandType);
			expected.setSecondaryCommand(secondaryCommandType);
			expected.setTaskName(taskName);
			expected.setIndex(index);

			// if an empty string is passed in, the command has no startDate
			if (startDate == "") {
				boost::posix_time::ptime expectedStartDate; // default constructor gives a not_a_date_time object
				expected.setStartDateTime(expectedStartDate);
			} else {
				boost::posix_time::ptime expectedStartDate(boost::posix_time::time_from_string(startDate));
				expected.setStartDateTime(expectedStartDate);
			}

			// if an empty string is passed in, the command has no endDate
			if (endDate == "") {
				boost::posix_time::ptime expectedEndDate; // default constructor gives a not_a_date_time object
				expected.setEndDateTime(expectedEndDate);
			} else {
				boost::posix_time::ptime expectedEndDate(boost::posix_time::time_from_string(endDate));
				expected.setEndDateTime(expectedEndDate);
			}

			return expected;
		}

		void compareCommandTokens(CommandTokens expected, CommandTokens actual) {

			Assert::AreEqual(int(expected.getPrimaryCommand()), int(actual.getPrimaryCommand()));
			Assert::AreEqual(int(expected.getSecondaryCommand()), int(actual.getSecondaryCommand()));
			Assert::AreEqual(expected.getTaskName(), actual.getTaskName());
			Assert::IsTrue(expected.getStartDateTime() == actual.getStartDateTime());
			Assert::IsTrue(expected.getEndDateTime() == actual.getEndDateTime());
			Assert::AreEqual(expected.getIndex(), actual.getIndex());

			std::vector<std::string> expectedTags, actualTags;
			expectedTags = expected.getTags();
			actualTags = actual.getTags();

			// checks if tags are both empty, else iterates through each element and assert equality
			Assert::AreEqual(expectedTags.empty(), actualTags.empty());
			if (!expectedTags.empty()) {
				for (unsigned i = 0; i < expectedTags.size(); i++) {
					Assert::AreEqual(expectedTags.at(i), actualTags.at(i));
				}
			}
		}
	};
}
