// MlLib.cpp : DLL 用にエクスポートされる関数を定義します。
//

#include "pch.h"
#include "framework.h"
#include "MlLib.h"
#include <vector>
#include <string>
#include <iostream>
#include <initializer_list>


#pragma region cpp 
namespace myk::lib {
#pragma region Matrixクラスの実装

	//コンストラクタ
	Matrix::Matrix(uint32_t row, uint32_t cul) : Matrix(row, cul, 0.0F) {}

	//コンストラクタ
	Matrix::Matrix(uint32_t row, uint32_t cul, double value) :
		ROW{ row }, CUL{ cul },
		matrix(row, std::vector<double>(cul, value)) { }

	// vectorをムーブして初期化するコンストラクタ
	Matrix::Matrix(const std::vector<std::vector<double>>&& matrix) : 
		matrix{ matrix }, ROW{ matrix.size() }, CUL{ matrix.at(0).size() } {}

	//vectorを参照して初期化するコンストラクタ
	Matrix::Matrix(const std::vector<std::vector<double>>& matrix) : 
		matrix{ matrix }, ROW{ matrix.size() }, CUL{ matrix.at(0).size() } {}

	// ムーブコンストラクタ
	Matrix::Matrix(Matrix&& from) noexcept :
		ROW{ from.ROW }, CUL{ from.CUL }, matrix(from.matrix) { }

	double& Matrix::at(uint32_t ROW, uint32_t CUL) noexcept(false) {
		return matrix.at(ROW).at(CUL);
	}

	double Matrix::read(uint32_t ROW, uint32_t CUL) const noexcept(false) {
		try {
			return matrix.at(ROW).at(CUL);
		} catch (std::out_of_range& e) {
			std::cerr << "Matrix::read で例外が発生しました:" << e.what() << std::endl;
		}
	}

	uint32_t Matrix::test() {
		return 321;
	}

#pragma endregion // Matrixクラス

	Matrix Multiply(const Matrix& lhs, const Matrix& rhs) noexcept(false) {
		using namespace std::literals::string_literals;
		if (lhs.CUL != rhs.ROW) {
			throw "計算できない行列です。\n左辺の行と右辺の列が一致している必要があります。\n"s
				+ "左辺 Matrix row = "s + std::to_string(lhs.ROW) + "cul = "s + std::to_string(lhs.CUL)
				+ "右辺 Matrix row = "s + std::to_string(rhs.ROW) + "cul = "s + std::to_string(rhs.CUL);
		}
		Matrix newMatr(rhs.CUL, lhs.ROW);
		for (size_t i = 0; i < rhs.CUL; ++i) {
			for (size_t j = 0; j < lhs.ROW; ++j) {
				//	newMatr.at(0, 0) = lhs.read(0, 0) * rhs.read(0, 0) + lhs.read(0, 1) * rhs.read(1, 0);
				for (size_t k = 0; k < lhs.CUL; ++k) {
					newMatr.at(i, j) += lhs.read(i, k) * rhs.read(k, j);
				}
			}
		}
		return newMatr;
	}

	Matrix&& operator*(const Matrix& lhs, const Matrix& rhs) noexcept(false) {
		return std::move(Multiply(lhs, rhs));
	}

	bool operator==(const Matrix& lhs, const Matrix& rhs) {
		//shapeチェック
		if (lhs.CUL != rhs.CUL || lhs.ROW != rhs.ROW) return false;
		for (size_t i = 0; i < lhs.ROW; ++i) {
			for (size_t j = 0; j < lhs.CUL; ++j) {
				//全要素チェック
				try {
					if (lhs.read(i, j) != rhs.read(i, j)) return false;
				} catch(std::out_of_range& e) {
					std::cerr << 
						"operator==(const Matrix&, const Matrix&)で例外が発生しました。:" <<
						e.what() << std::endl;
					//return false;
				}
			}
		}
		return true;
	}

} //namespace end myk::lib

#pragma endregion


myk::lib::Matrix GetMatrix(uint32_t ROW, uint32_t CUL) {
	return myk::lib::Matrix(ROW, CUL);
}

#pragma region CS向けに公開

// これは、エクスポートされた変数の例です
//MLLIB_API int nMlLib=0;

// これは、エクスポートされた関数の例です。
int fnMlLib(void) {
	std::cout << "fnMlLiv が実行されました" << std::endl;
    return 100 * 3;
}
#pragma endregion

