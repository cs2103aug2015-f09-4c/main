//@@author A0097681N
#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ParserTest {
	TEST_CLASS(ParserTester) {
	public:
		Parser _parser;

		TEST_METHOD(unitTest_parser_TokeniseAddFromTo) {
			std::string testUserInput = "ADD activityTask FROM 2002-01-20 23:59:59.000 TO 2002-01-22 23:59:59.000";
			CommandTokens actual, expected;

			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Add,
			                                      CommandTokens::SecondaryCommandType::FromTo,
			                                      "activityTask",
			                                      "2002-01-20 23:59:59.000",
			                                      "2002-01-22 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseAddBy) {
			std::string testUserInput = "ADD todoTask BY 2002-01-22 23:59:59.000";
			CommandTokens actual, expected;

			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Add,
			                                      CommandTokens::SecondaryCommandType::By,
			                                      "todoTask",
			                                      "",
			                                      "2002-01-22 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseAddFloating) {
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

		TEST_METHOD(unitTest_parser_TokeniseComplete) {
			std::string testUserInput = "COMPLETE 11";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::MarkAsComplete,
			                                      CommandTokens::SecondaryCommandType::Index,
			                                      "",
			                                      "",
			                                      "",
			                                      11);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseConfigureSaveLocation) {
			std::string testUserInput = "CONFIGURE SAVE LOCATION D:\\";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Configure,
			                                      CommandTokens::SecondaryCommandType::SaveLocation,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);

			expected.setOtherCommandParameter("D:\\");
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

		TEST_METHOD(unitTest_parser_TokeniseDeleteCompleted) {
			std::string testUserInput = "DELETE COMPLETED";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Delete,
			                                      CommandTokens::SecondaryCommandType::Completed,
			                                      "",
			                                      "",
			                                      "",
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

		TEST_METHOD(unitTest_parser_TokeniseDeleteBy) {
			std::string testUserInput = "DELETE BY 2002-01-22 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Delete,
			                                      CommandTokens::SecondaryCommandType::By,
			                                      "",
			                                      "",
			                                      "2002-01-22 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseDeleteFromTo) {
			std::string testUserInput = "DELETE FROM 2002-01-20 23:59:59.000 TO 2002-01-22 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Delete,
			                                      CommandTokens::SecondaryCommandType::FromTo,
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

		TEST_METHOD(unitTest_parser_TokeniseDisplayActivity) {
			std::string testUserInput = "DISPLAY ACTIVITY";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Display,
			                                      CommandTokens::SecondaryCommandType::FromTo,
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

		TEST_METHOD(unitTest_parser_TokeniseDisplayTodo) {
			std::string testUserInput = "DISPLAY TODO";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Display,
			                                      CommandTokens::SecondaryCommandType::By,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseEditName) {
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

		TEST_METHOD(unitTest_parser_TokeniseEditStartDate) {
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

		TEST_METHOD(unitTest_parser_TokeniseEditEndDate) {
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

		TEST_METHOD(unitTest_parser_TokeniseExport) {
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

		TEST_METHOD(unitTest_parser_TokeniseImport) {
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

		TEST_METHOD(unitTest_parser_TokeniseRefresh) {
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

		TEST_METHOD(unitTest_parser_TokeniseSearchName) {
			std::string testUserInput = "SEARCH NAME a Random Task";
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

		TEST_METHOD(unitTest_parser_TokeniseSearchFromTo) {
			std::string testUserInput = "SEARCH FROM 2002-01-20 23:59:59.000 TO 2002-01-22 23:59:59.000";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Search,
			                                      CommandTokens::SecondaryCommandType::FromTo,
			                                      "",
			                                      "2002-01-20 23:59:59.000",
			                                      "2002-01-22 23:59:59.000",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSearchFreeSlot) {
			std::string testUserInput = "SEARCH FREE";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Search,
			                                      CommandTokens::SecondaryCommandType::FreeSlot,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSearchStartBefore) {
			std::string testUserInput = "SEARCH START BEFORE 2002-01-20 23:59:59.000";
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

		TEST_METHOD(unitTest_parser_TokeniseSearchStartAfter) {
			std::string testUserInput = "SEARCH START AFTER 2002-01-20 23:59:59.000";
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

		TEST_METHOD(unitTest_parser_TokeniseSearchEndBefore) {
			std::string testUserInput = "SEARCH END BEFORE 2002-01-20 23:59:59.000";
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

		TEST_METHOD(unitTest_parser_TokeniseSearchEndAfter) {
			std::string testUserInput = "SEARCH END AFTER 2002-01-20 23:59:59.000";
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

		TEST_METHOD(unitTest_parser_TokeniseSearchTags) {
			std::string testUserInput = "SEARCH TAGS #123";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Search,
			                                      CommandTokens::SecondaryCommandType::Tags,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);
			std::vector<std::string> newTags;
			newTags.push_back("#123");
			expected.setTags(newTags);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSortName) {
			std::string testUserInput = "SORT NAME";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Sort,
			                                      CommandTokens::SecondaryCommandType::Name,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);
			
			expected.setOtherCommandParameter("Ascending");
			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSortNameDesc) {
			std::string testUserInput = "SORT NAME DESC";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Sort,
			                                      CommandTokens::SecondaryCommandType::Name,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);
			
			expected.setOtherCommandParameter("Descending");
			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSortStart) {
			std::string testUserInput = "SORT START";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Sort,
			                                      CommandTokens::SecondaryCommandType::Start,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);
			
			expected.setOtherCommandParameter("Ascending");
			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSortStartDesc) {
			std::string testUserInput = "SORT START DESC";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Sort,
			                                      CommandTokens::SecondaryCommandType::Start,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);
			
			expected.setOtherCommandParameter("Descending");
			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSortEnd) {
			std::string testUserInput = "SORT END";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Sort,
			                                      CommandTokens::SecondaryCommandType::End,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);
			
			expected.setOtherCommandParameter("Ascending");
			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseSortEndDesc) {
			std::string testUserInput = "SORT END DESC";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Sort,
			                                      CommandTokens::SecondaryCommandType::End,
			                                      "",
			                                      "",
			                                      "",
			                                      -1);
			
			expected.setOtherCommandParameter("Descending");
			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseTag) {
			std::string testUserInput = "TAG 19 #123 #abc";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Tag,
			                                      CommandTokens::SecondaryCommandType::Index,
			                                      "",
			                                      "",
			                                      "",
			                                      19);
			std::vector<std::string> newTags;
			newTags.push_back("#123");
			newTags.push_back("#abc");
			expected.setTags(newTags);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_TokeniseUndo) {
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

		TEST_METHOD(unitTest_parser_TokeniseUntag) {
			std::string testUserInput = "UNTAG 23 #12c #ab3";
			CommandTokens actual, expected;
			actual = _parser.parse(testUserInput);
			expected = buildExpectedCommandTokens(CommandTokens::PrimaryCommandType::Untag,
			                                      CommandTokens::SecondaryCommandType::Index,
			                                      "",
			                                      "",
			                                      "",
			                                      23);
			std::vector<std::string> newTags;
			newTags.push_back("#12c");
			newTags.push_back("#ab3");
			expected.setTags(newTags);

			compareCommandTokens(expected, actual);
		}

		TEST_METHOD(unitTest_parser_DateParser_DD_MM_YYYY_HHHH) {
			std::string testUserInputDate = "13-05-1999 1320";

			boost::posix_time::ptime expected(boost::posix_time::time_from_string("1999-05-13 13:20:00.000"));
			boost::posix_time::ptime actual;
			actual = DateParser::parse(testUserInputDate);

			Assert::IsTrue(expected == actual);
		}

		TEST_METHOD(unitTest_parser_DateParser_DD_MM_YYYY) {
			std::string testUserInputDate = "13-05-1999";

			boost::posix_time::ptime expected(boost::posix_time::time_from_string("1999-05-13 00:00:00.000"));
			boost::posix_time::ptime actual;
			actual = DateParser::parse(testUserInputDate);

			Assert::IsTrue(expected == actual);
		}

		// upper boundary case for valid date range partition
		TEST_METHOD(unitTest_parser_DateParser_DD_MM_YYYY_HHHH_MaxRange) {
			std::string testUserInputDate = "31-12-9999 2359";

			boost::posix_time::ptime expected(boost::posix_time::time_from_string("9999-12-31 23:59:00.000"));
			boost::posix_time::ptime actual;
			actual = DateParser::parse(testUserInputDate);

			Assert::IsTrue(expected == actual);
		}

		// lower boundary case for valid date range partition
		TEST_METHOD(unitTest_parser_DateParser_DD_MM_YYYY_HHHH_MinRange) {
			std::string testUserInputDate = "01-01-1400 0000";

			boost::posix_time::ptime expected(boost::posix_time::time_from_string("1400-01-01 00:00:00.000"));
			boost::posix_time::ptime actual;
			actual = DateParser::parse(testUserInputDate);

			Assert::IsTrue(expected == actual);
		}

		// edge cases partition: dates that are invalid because of non-uniform length of months
		TEST_METHOD(unitTest_parser_DateParser_DD_MM_YYYY_HHHH_InvalidDate) {
			std::string testUserInputDate = "29-02-1999 1345";

			boost::posix_time::ptime expected;
			boost::posix_time::ptime actual;
			actual = DateParser::parse(testUserInputDate);

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
			Assert::AreEqual(expected.getOtherCommandParameter(), actual.getOtherCommandParameter());

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
