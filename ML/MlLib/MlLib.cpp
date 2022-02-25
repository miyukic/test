// MlLib.cpp : DLL 用にエクスポートされる関数を定義します。
//

#include "pch.h"
#include "framework.h"
#include "MlLib.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <initializer_list>


#pragma region cpp 
namespace myk::lib {
#pragma region Matrixクラスの実装

	// コンストラクタ
	// 要素は初期化しない
	//Matrix::Matrix(uint32_t row, uint32_t cul) : Matrix(row, cul, 0.0F) {}
	Matrix::Matrix(uint32_t row, uint32_t cul) :
		ROW{ row }, CUL{ cul }, matrix(row, std::vector<double>(cul))
	{}

	// コンストラクタ
	Matrix::Matrix(uint32_t row, uint32_t cul, double value) :
		ROW{ row }, CUL{ cul },
		matrix(row, std::vector<double>(cul, value)) { }

	// vectorをムーブして初期化するコンストラクタ
	Matrix::Matrix(const std::vector<std::vector<double>>&& matrix) :
		matrix{ matrix }, ROW{ matrix.size() }, CUL{ matrix.at(0).size() } {
		// 妥協の産物...ジャグ配列を禁止にしたい
		// テンプレートを使わずに二次元目の要素数を固定する方法
		checkMatrixCULSize();
	}

	// vectorを参照して初期化するコンストラクタ
	Matrix::Matrix(const std::vector<std::vector<double>>& matrix) : 
		matrix{ matrix }, ROW{ matrix.size() }, CUL{ matrix.at(0).size() } {
		checkMatrixCULSize();
	}

	// vectorをムーブして初期化するコンストラクタ(ジャグ配列チェックしない場合はtrue)
	Matrix::Matrix(const std::vector<std::vector<double>>&& matrix, bool unCheckJaddedArray) : 
		matrix{ matrix }, ROW{ matrix.size() }, CUL{ matrix.at(0).size() } {
		if (!unCheckJaddedArray) checkMatrixCULSize();
	}

	// vectorを参照して初期化するコンストラクタ(ジャグ配列チェックをしない場合はtrue)
	Matrix::Matrix(const std::vector<std::vector<double>>& matrix, bool unCheckJaddedArray) : 
		matrix{ matrix }, ROW{ matrix.size() }, CUL{ matrix.at(0).size() } {
		if (!unCheckJaddedArray) checkMatrixCULSize();
	}

	// ムーブコンストラクタ
	Matrix::Matrix(Matrix&& from) noexcept :
		ROW{ from.ROW }, CUL{ from.CUL }, matrix(from.matrix) { }

	// 行と列を指定してその要素の参照を取得（変更可）
	double& Matrix::at(uint32_t ROW, uint32_t CUL) noexcept(false) {
		return matrix.at(ROW).at(CUL);
	}

	// 行と列を指定してその要素の値を取得（変更不可）
	double Matrix::read(uint32_t ROW, uint32_t CUL) const noexcept(false) {
		try {
			return matrix.at(ROW).at(CUL);
		} catch (std::out_of_range& e) {
			std::cerr << "Matrix::read で例外が発生しました:" << e.what() << std::endl;
			return 0;
		}
	}

	// Matrixの内容を出力する
	std::string Matrix::print() {
//#ifdef _MSC_VER
		//const WCHAR hazime= '{ ';
		//const WCHAR owari = ' }';
//#else
//#if __cplusplus > 
		const char* hazime	= "{";
		const char* owari	= "}";
		const char* margin	= " ";
//#endif
		static constexpr uint8_t CAP = 6 * 10;
		std::stringstream sst;
		sst		<< "\n"
				<< "――――――――――――\n"
				<< "行数: " << ROW << "\n"
				<< "列数: " << CUL << "\n"
				<< "――――――――――――\n";
		sst << hazime << "\n";
		for (std::vector<double> vec : matrix) {
			sst << "\t" << hazime << margin;
			for (size_t i = 0; i < vec.size(); ++i) {
				sst << vec.at(i);
				if (i != (vec.size() - 1)) sst << ", ";
			}
			sst << margin << owari << "\n";
		}
		sst << owari << std::endl;
		std::cout << sst.str();
		return sst.str();
	}

	bool Matrix::checkMatrixCULSize() noexcept(false) {
		for (size_t i = 0; i < matrix.size(); ++i) {
			if (matrix.at(i).size() != CUL) throw "Matrixの列サイズが一致していません。";
		}
	}

	uint32_t Matrix::test() {
		return 321 * 42 + 12 * 3;
	}

#pragma endregion // Matrixクラス

#pragma region myk::libのグローバル関数
	// 行列積
	Matrix multiply(const Matrix& lhs, const Matrix& rhs) noexcept(false) {
		using namespace std::literals::string_literals;
		if (lhs.CUL != rhs.ROW) {
			throw "計算できない行列です。\n左辺の行と右辺の列が一致している必要があります。\n"s
				+ "左辺 Matrix row = "s + std::to_string(lhs.ROW) + "cul = "s + std::to_string(lhs.CUL)
				+ "右辺 Matrix row = "s + std::to_string(rhs.ROW) + "cul = "s + std::to_string(rhs.CUL);
		}
		Matrix newMatr(lhs.ROW, rhs.CUL);
		for (size_t r = 0; r < lhs.ROW; ++r) {
			for (size_t c = 0; c < rhs.CUL; ++c) {
				//	newMatr.at(0, 0) = lhs.read(0, 0) * rhs.read(0, 0) + lhs.read(0, 1) * rhs.read(1, 0);
				for (size_t k = 0; k < lhs.CUL; ++k) {
					newMatr.at(r, c) += lhs.read(r, k) * rhs.read(k, c);
				}
			}
		}
		return newMatr;
	}

	// 行列スカラー倍
	Matrix multiply(const Matrix& lhs, double rhs) noexcept(false) {
		Matrix newMatrix(lhs.ROW, lhs.CUL);
		auto r = lhs.ROW;
		auto c = lhs.CUL;
		for (size_t i = 0; i < lhs.ROW; ++i) {
			for (size_t j = 0; j < lhs.CUL; ++j) {
				try {
					newMatrix.at(i, j)
						= lhs.read(i, j) * rhs;
				} catch (std::out_of_range& e) {
					std::cout << "multiply(const MAtrix&, double) " << e.what() << std::endl;
				}
			}
		}
		return newMatrix;
	}

	// 行列各要素に加算する
	Matrix add(const Matrix& lhs, double rhs) noexcept(false) {
		Matrix newMatrix(lhs.ROW, lhs.CUL);
		for (size_t i = 0; i < lhs.ROW; ++i) {
			for (size_t j = 0; j < lhs.CUL; ++j) {
				newMatrix.at(i, j) = lhs.read(i, j) + rhs;
			}
		}
		return newMatrix;
	}

	Matrix operator*(const Matrix& lhs, const Matrix& rhs) noexcept(false) {
		return multiply(lhs, rhs);
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
#pragma endregion //myk::libのグローバル関数

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
