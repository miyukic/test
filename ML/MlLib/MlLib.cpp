// MlLib.cpp : DLL 用にエクスポートされる関数を定義します。
//

#include "pch.h"
#include "framework.h"
#include "MlLib.h"
#include <vector>
#include <string>


#pragma region cpp 
namespace myk::lib {
#pragma region Matrixクラスの実装

	/// <summary>
	/// 行と列を指定して行列オブジェクトを生成します。
	/// </summary>
	/// <param name="row"></param>
	/// <param name="cul"></param>
	Matrix::Matrix(uint32_t row, uint32_t cul) :
		ROW{ row }, CUL{ cul }, matrix(ROW, std::vector<double>(CUL, 0.0)) { }

	/// <summary>
	/// 行と列を指定してその要素の参照を返します。
	/// ※注意 インデックスは0始まりです。
	/// </summary>
	/// <param name="ROW"></param>
	/// <param name="CUL"></param>
	/// <returns></returns>
	double& Matrix::at(uint32_t ROW, uint32_t CUL) noexcept(false) {
		return matrix.at(ROW).at(CUL);
	}

	/// <summary>
	/// 行と列を指定して値を読みます
	/// ※注意 インデックスは0始まりです。
	/// </summary>
	/// <param name="ROW"></param>
	/// <param name="CUL"></param>
	/// <returns></returns>
	double Matrix::read(uint32_t ROW, uint32_t CUL) const noexcept(false) {
		return matrix.at(ROW).at(CUL);
	}

	uint32_t Matrix::test() {
		return 321;
	}

#pragma endregion // Matrixクラス
		Matrix Multiply(const Matrix& lhs, const Matrix& rhs) noexcept(false) {
		using namespace std::literals::string_literals;
		if (lhs.ROW != rhs.CUL) {
			throw "計算できない行列です。\n左辺の行と右辺の列が一致している必要があります。\n"s
				+ "左辺 Matrix row = "s + std::to_string(lhs.ROW) + "cul = "s + std::to_string(lhs.CUL)
				+ "右辺 Matrix row = "s + std::to_string(rhs.ROW) + "cul = "s + std::to_string(rhs.CUL);
		}
		Matrix newMatr(rhs.ROW, lhs.CUL);
		for (size_t i = 0; i < rhs.ROW; ++i) {
			for (size_t j = 0; j < lhs.CUL; ++j) {
				//for ()
				//	newMatr.at(i, j)
				//	newMatr.at(0, 0) = lhs.read(0, 0) * rhs.read(0, 0) + lhs.read(0, 1) * rhs.read(1, 0);
				newMatr.at(1, 0) = lhs.read(1, 0) * rhs.read(0, 0) + lhs.read(1, 1) * rhs.read(1, 0);

				newMatr.at(0, 1) = lhs.read(0, 0) * rhs.read(0, 1) + lhs.read(0, 1) * rhs.read(1, 1);
				newMatr.at(1, 1) = lhs.read(1, 0) * rhs.read(0, 1) + lhs.read(1, 1) * rhs.read(1, 1);
			}
		}
		return newMatr;
	}
} //namespace end myk::lib

/// <summary>
/// 
/// </summary>
/// <param name="lhs"></param>
/// <param name="rhs"></param>
/// <returns></returns>

#pragma endregion


// これは、エクスポートされた変数の例です
//MLLIB_API int nMlLib=0;

// これは、エクスポートされた関数の例です。
int fnMlLib(void)
{
    return 256 * 3;
}


// これは、エクスポートされたクラスのコンストラクターです。
//CMlLib::CMlLib()
//{
//    return;
//}
