#include <vector>
#include "pch.h"
#include "CppUnitTest.h"
#include "../MlLib/MlLib.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace myk::lib;

namespace UnitTestMiLib
{
	TEST_CLASS(UnitTestMiLib)
	{
	public:
		
		TEST_METHOD(Matrixクラスの＝演算子) {
			std::vector<std::vector<double>> vec1 = { { 1, 2, 3 }, {2, 3, 4} };
			std::vector<std::vector<double>> vec2 = { { 2, 2, 3 }, {2, 4, 4} };
			//行列が同じ場合のチェック
			Matrix mtx1{ vec1 };
			Matrix mtx2( vec1 );
			bool result = (mtx1 == mtx2);
			Assert::AreEqual(true, result);
			//異なる場合のチェック
			Matrix mtx3{ vec2 };
			bool result = (mtx1 == mtx3);
			Assert::AreEqual(false, result);
		}

		TEST_METHOD(Multiply関数) {
			Matrix mtx(10, 10);
		}

		TEST_METHOD(テスト2) {
		}

	};
}
