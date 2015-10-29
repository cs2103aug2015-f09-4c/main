#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest {
	TEST_CLASS(ParserTester) {
	public:
		Parser _parser;

		TEST_METHOD(unitTest_parser_TokeniseAddActivityCommand) {
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

		TEST_METHOD(unitTest_parser_TokeniseAddTodoCommand) {
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

		TEST_METHOD(unitTest_parser_TokeniseAddFloatingCommand) {
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

		TEST_METHOD(unitTest_parser_TokeniseCompleteCommand) {
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

		TEST_METHOD(unitTest_parser_TokeniseDeleteFromTo) {
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

		TEST_METHOD(unitTest_parser_TokeniseDeleteFrom) {
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

		TEST_METHOD(unitTest_parser_TokeniseDeleteAll) {
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

		TEST_METHOD(unitTest_parser_TokeniseDeleteBy) {
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

		TEST_METHOD(unitTest_parser_TokeniseDeleteIndex) {
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

		TEST_METHOD(unitTest_parser_TokeniseDisplayBy) {
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

		TEST_METHOD(unitTest_parser_TokeniseDisplayFrom) {
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

		TEST_METHOD(unitTest_parser_TokeniseDisplayAll) {
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

		TEST_METHOD(unitTest_parser_TokeniseDisplayFloating) {
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

		TEST_METHOD(unitTest_parser_TokeniseEditNameCommand) {
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

		TEST_METHOD(unitTest_parser_TokeniseEditStartDateCommand) {
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

		TEST_METHOD(unitTest_parser_TokeniseEditEndDateCommand) {
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

		TEST_METHOD(unitTest_parser_TokeniseExportCommand) {
			std::string testUserInput = "EXPORT C:\\";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Export,
			                                      CommandTokens::SecondaryCommandType::None,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);
			expected.setOtherCommandParameter("C:\\");

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseImportCommand) {
			std::string testUserInput = "IMPORT D:\\aRandomFile.txt";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Import,
			                                      CommandTokens::SecondaryCommandType::None,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);
			expected.setOtherCommandParameter("D:\\aRandomFile.txt");

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseRefreshCommand) {
			std::string testUserInput = "REFRESH";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Refresh,
			                                      CommandTokens::SecondaryCommandType::None,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSearchNameCommand) {
			std::string testUserInput = "Search Name a Random Task";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Search,
			                                      CommandTokens::SecondaryCommandType::Name,
			                                      "a Random Task",
			                                      "",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSearchStartBeforeCommand) {
			std::string testUserInput = "Search Start Before 2002-01-20 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Search,
			                                      CommandTokens::SecondaryCommandType::StartBefore,
			                                      "",
			                                      "2002-01-20 23:59:59.000",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSearchStartAfterCommand) {
			std::string testUserInput = "Search Start After 2002-01-20 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Search,
			                                      CommandTokens::SecondaryCommandType::StartAfter,
			                                      "",
			                                      "2002-01-20 23:59:59.000",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSearchEndBeforeCommand) {
			std::string testUserInput = "Search End Before 2002-01-20 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Search,
			                                      CommandTokens::SecondaryCommandType::EndBefore,
			                                      "",
			                                      "",
			                                      "2002-01-20 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSearchEndAfterCommand) {
			std::string testUserInput = "Search End After 2002-01-20 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Search,
			                                      CommandTokens::SecondaryCommandType::EndAfter,
			                                      "",
			                                      "",
			                                      "2002-01-20 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSearchTagsCommand) {
			std::string testUserInput = "Search Tags #123";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Search,
			                                      CommandTokens::SecondaryCommandType::Tags,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);
			std::vector< std::string > newTags;
			newTags.push_back("#123");
			expected.setTags(newTags);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseTagCommand) {
			std::string testUserInput = "TAG 19 #123 #abc";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Tag,
			                                      CommandTokens::SecondaryCommandType::Index,
			                                      "",
			                                      "",
			                                      "",
			                                      19);
			std::vector< std::string > newTags;
			newTags.push_back("#123");
			newTags.push_back("#abc");
			expected.setTags(newTags);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseUndoCommand) {
			std::string testUserInput = "UNDO";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Undo,
			                                      CommandTokens::SecondaryCommandType::None,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseUntagCommand) {
			std::string testUserInput = "UNTAG 23 #12c #ab3";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Untag,
			                                      CommandTokens::SecondaryCommandType::Index,
			                                      "",
			                                      "",
			                                      "",
			                                      23);
			std::vector< std::string > newTags;
			newTags.push_back("#12c");
			newTags.push_back("#ab3");
			expected.setTags(newTags);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_DateParser_DD_MM_YYYY_HHHH) {
			std::string testUserInputDate = "13-05-1999 1320";
			DateParser dateParser;

			boost::posix_time::ptime expected(boost::posix_time::time_from_string("1999-05-13 13:20:00.000"));
			boost::posix_time::ptime actual;
			actual = dateParser.parse(testUserInputDate);
			
			Assert::IsTrue(expected == actual);
		}

		// upper boundary case for valid date range partition
		TEST_METHOD(unitTest_parser_DateParser_DD_MM_YYYY_HHHH_MaxRange) {
			std::string testUserInputDate = "31-12-9999 2359";
			DateParser dateParser;

			boost::posix_time::ptime expected(boost::posix_time::time_from_string("9999-12-31 23:59:00.000"));
			boost::posix_time::ptime actual;
			actual = dateParser.parse(testUserInputDate);
			
			Assert::IsTrue(expected == actual);
		}
		
		// lower boundary case for valid date range partition
		TEST_METHOD(unitTest_parser_DateParser_DD_MM_YYYY_HHHH_MinRange) {
			std::string testUserInputDate = "01-01-1400 0000";
			DateParser dateParser;

			boost::posix_time::ptime expected(boost::posix_time::time_from_string("1400-01-01 00:00:00.000"));
			boost::posix_time::ptime actual;
			actual = dateParser.parse(testUserInputDate);
			
			Assert::IsTrue(expected == actual);
		}		
		
		// edge cases partition: dates that are invalid because of non-uniform length of months
		TEST_METHOD(unitTest_parser_DateParser_DD_MM_YYYY_HHHH_InvalidDate) {
			std::string testUserInputDate = "29-02-1999 1345";
			DateParser dateParser;

			boost::posix_time::ptime expected;
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
