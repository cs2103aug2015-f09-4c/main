#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LogicTest
{		
	TEST_CLASS(CommandCreatorTest)
	{
	public:
		
		TEST_METHOD(PROCESS_ADD_FLOATING)
		{
			std::vector<std::string> details;
			details.push_back("");
			CommandTokens tokens(Add, Floating, details);
			CommandCreator creator;
			AddCommand command = creator.testProcessAddCommand(tokens);
			Assert::AreEqual(true, command.getPrimaryCommandType() == Add);
			Assert::AreEqual(true, command.getSecondaryCommandType() == Floating);
			Assert::AreEqual(std::string(""), command.getTask().getTaskText());
		}
	};

	TEST_CLASS (StorageHandlerTest)
	{
	public:

		TEST_METHOD(ADD)
		{

		}
	};
}