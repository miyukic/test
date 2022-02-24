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
		
		TEST_METHOD(Matrix�N���X�́����Z�q) {
			std::vector<std::vector<double>> vec1 = { { 1, 2, 3 }, {2, 3, 4} };
			std::vector<std::vector<double>> vec2 = { { 2, 2, 3 }, {2, 4, 4} };
			//�s�񂪓����ꍇ�̃`�F�b�N
			Matrix mtx1{ vec1 };
			Matrix mtx2( vec1 );
			bool result = (mtx1 == mtx2);
			Assert::AreEqual(true, result);
			//�قȂ�ꍇ�̃`�F�b�N
			Matrix mtx3{ vec2 };
			bool result2 = (mtx1 == mtx3);
			Assert::AreEqual(false, result2);
		}

		TEST_METHOD(�ے�I�����Z�q) {
			Matrix mtx1({ {3, 2, 5}, {2, 4, 5} });
			//ToDo
		}

		TEST_METHOD(Multiply�֐�) {
			Matrix mtx1({ {3, 2, 5}, {2, 4, 5} });
			Matrix mtx2({ {3, 2, 5}, {2, 4, 5} });
		}

		TEST_METHOD(�e�X�g2) {
		}

	};
}
