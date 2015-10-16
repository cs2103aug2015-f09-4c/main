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
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Add,
			                                      CommandTokens::SecondaryCommandType::Timed,
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
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Add,
			                                      CommandTokens::SecondaryCommandType::Todo,
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
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Add,
			                                      CommandTokens::SecondaryCommandType::Floating,
			                                      "floatingTask",
			                                      "",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseDeleteFromTo) {
			std::string testUserInput = "DELETE FROM 2002-01-20 23:59:59.000 TO 2002-01-22 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Delete,
			                                      CommandTokens::SecondaryCommandType::Timed,
			                                      "",
			                                      "2002-01-20 23:59:59.000",
			                                      "2002-01-22 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseDeleteFrom) {
			std::string testUserInput = "DELETE FROM 2002-01-20 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Delete,
			                                      CommandTokens::SecondaryCommandType::Start,
			                                      "",
			                                      "2002-01-20 23:59:59.000",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseDeleteAll) {
			std::string testUserInput = "DELETE ALL";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Delete,
			                                      CommandTokens::SecondaryCommandType::All,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseDeleteBy) {
			std::string testUserInput = "DELETE BY 2002-01-22 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Delete,
			                                      CommandTokens::SecondaryCommandType::Todo,
			                                      "",
			                                      "",
			                                      "2002-01-22 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseDeleteIndex) {
			std::string testUserInput = "DELETE 3";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Delete,
			                                      CommandTokens::SecondaryCommandType::Index,
			                                      "",
			                                      "",
			                                      "",
			                                      3);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseDisplayBy) {
			std::string testUserInput = "DISPLAY BY 2002-01-22 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Display,
			                                      CommandTokens::SecondaryCommandType::Todo,
			                                      "",
			                                      "",
			                                      "2002-01-22 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseDisplayFrom) {
			std::string testUserInput = "DISPLAY FROM 2002-01-20 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Display,
			                                      CommandTokens::SecondaryCommandType::Start,
			                                      "",
			                                      "2002-01-20 23:59:59.000",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseDisplayAll) {
			std::string testUserInput = "DISPLAY ALL";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Display,
			                                      CommandTokens::SecondaryCommandType::All,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseDisplayFloating) {
			std::string testUserInput = "DISPLAY FLOATING";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Display,
			                                      CommandTokens::SecondaryCommandType::Floating,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseEditNameCommand) {
			std::string testUserInput = "EDIT NAME 3 newTaskName";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Edit,
			                                      CommandTokens::SecondaryCommandType::Name,
			                                      "newTaskName",
			                                      "",
			                                      "",
			                                      3);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseEditStartDateCommand) {
			std::string testUserInput = "EDIT START 5 2002-01-20 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Edit,
			                                      CommandTokens::SecondaryCommandType::Start,
			                                      "",
			                                      "2002-01-20 23:59:59.000",
			                                      "",
			                                      5);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseEditEndDateCommand) {
			std::string testUserInput = "EDIT END 7 2002-01-20 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Edit,
			                                      CommandTokens::SecondaryCommandType::End,
			                                      "",
			                                      "",
			                                      "2002-01-20 23:59:59.000",
			                                      7);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testTokeniseCompleteCommand) {
			std::string testUserInput = "COMPLETE 11";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Complete,
			                                      CommandTokens::SecondaryCommandType::Index,
			                                      "",
			                                      "",
			                                      "",
			                                      11);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(testDateParser_DD_MM_YYYY_HHHH) {
			std::string testUserInputDate = "13-05-1999 1320";
			DateParser dateParser;

			boost::posix_time::ptime expected(boost::posix_time::time_from_string("1999-05-13 13:20:00.000"));
			boost::posix_time::ptime actual;
			actual = dateParser.parse(testUserInputDate);

			Assert::IsTrue(expected == actual);
		}

		CommandTokens buildExpectedCommandTokens(CommandTokens::PrimaryCommandType primaryCommandType,
		                                         CommandTokens::SecondaryCommandType secondaryCommandType,
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
				boost::posix_time::ptime notAPtime; // default constructor gives a not_a_date_time object
				expected.setStartDateTime(notAPtime);
			} else {
				boost::posix_time::ptime expectedStartDate(boost::posix_time::time_from_string(startDate));
				expected.setStartDateTime(expectedStartDate);
			}

			// if an empty string is passed in, the command has no endDate
			if (endDate == "") {
				boost::posix_time::ptime notAPtime; // default constructor gives a not_a_date_time object
				expected.setEndDateTime(notAPtime);
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
