#include "pch.h"
#include "CppUnitTest.h"
#include "../LibraryTest/LibraryTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestStudy
{
	TEST_CLASS(UnitTestStudy)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			CLibraryTest st;
			int a = st.GetNumber();
			Assert::AreEqual(321, a);
		}
	};
}
