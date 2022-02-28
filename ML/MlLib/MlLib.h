// 以下の ifdef ブロックは、DLL からのエクスポートを容易にするマクロを作成するための
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された MLLIB_EXPORTS
// シンボルを使用してコンパイルされます。このシンボルは、この DLL を使用するプロジェクトでは定義できません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、
// MLLIB_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef MLLIB_EXPORTS
#	define MLLIB_API __declspec(dllexport)
#else
#	ifdef _WINDLL
#		define MLLIB_API __declspec(dllimport)
#	elif __linux__
#		define MLLIB_API
#	endif
#endif
#pragma once
#include <vector>
#include <initializer_list>
#include <string>
#include <memory>

namespace myk {
	namespace lib {

		class MLLIB_API Matrix {
			std::vector<std::vector<double>> matrix;
		public:
			const uint32_t ROW = 1;
			const uint32_t CUL = 1;

			/// <summary>
			/// 行と列を指定して行列オブジェクトを生成します。
			/// 値はすべて0.0Fになる。
			/// Matrixクラスのコンストラクタ。
			/// </summary>
			/// <param name="row"></param>
			/// <param name="cul"></param>
			Matrix(uint32_t row, uint32_t cul);

			/// <summary>
			/// 行と列とその要素を指定して行列オブジェクトを生成します。
			/// Matrixのコンストラクタ。
			/// </summary>
			/// <param name="row"></param>
			/// <param name="cul"></param>
			/// <param name="value"></param>
			Matrix(uint32_t row, uint32_t cul, double value);

			/// <summary>
			/// vectorオブジェクトをムーブしてMatrixオブジェクトを生成します。
			/// Matrixのコンストラクタ。
			/// </summary>
			Matrix(const std::vector<std::vector<double>>&& mtrix);

			/// <summary>
			/// vectorオブジェクトを参照してMatrixオブジェクトを生成します。
			/// Matrixのコンストラクタ。
			/// </summary>
			Matrix(const std::vector<std::vector<double>>& mtrix);

			/// <summary>
			/// vectorをムーブして初期化するコンストラクタ。
			/// </summary>
			/// <param name="matrix"></param>
			/// <param name="unCheckJaddedArray">ジャグ配列チェックをしない場合は true </param>
			Matrix(const std::vector<std::vector<double>>&& matrix, bool unCheckJaddedArray);

			/// <summary>
			/// vectorを参照して初期化するコンストラクタ。
			/// </summary>
			/// <param name="matrix"></param>
			/// <param name="unCheckJaddedArray">ジャグ配列チェックをしない</param>
			Matrix(const std::vector<std::vector<double>>& matrix, bool unCheckJaddedArray);

			/// <summary>
			/// Matrixのムーブコンストラクタ
			/// </summary>
			Matrix(Matrix && from) noexcept;


			/// <summary>
			/// 行と列を指定してその要素の参照を返します。
			/// ※注意 インデックスは0始まりです。
			/// </summary>
			/// <param name="ROW"></param>
			/// <param name="CUL"></param>
			/// <returns></returns>
			double& at(uint32_t ROW, uint32_t CUL) noexcept(false);

			/// <summary>
			/// 行と列を指定して値を読みます
			/// ※注意 インデックスは0始まりです。
			/// </summary>
			/// <param name="ROW"></param>
			/// <param name="CUL"></param>
			/// <returns></returns>
			double read(uint32_t ROW, uint32_t CUL) const noexcept(false);

			/// <summary>
			/// Matrix の内容を標準出力に出力します。
			/// </summary>
			/// <returns>出力の内容を返します。</returns>
			std::string print();

			uint32_t test();
		private:
			 
			bool checkMatrixCULSize() noexcept(false);
		};

		/// <summary>
		/// 行列積
		/// </summary>
		/// <param name="lhs"></param>
		/// <param name="rhs"></param>
		/// <returns></returns>
		MLLIB_API Matrix multiply(const Matrix& lhs, const Matrix& rhs) noexcept(false);

		/// <summary>
		/// 行列をスカラー倍
		/// </summary>
		/// <param name="lhs"></param>
		/// <param name="rhs"></param>
		/// <returns></returns>
		MLLIB_API Matrix multiply(const Matrix& lhs, double rhs) noexcept(false);

		/// <summary>
		/// 行列各要素にadd
		/// </summary>
		/// <param name="lhs"></param>
		/// <param name="rhs"></param>
		/// <returns></returns>
		MLLIB_API Matrix add(const Matrix& lhs, double rhs) noexcept(false);

		MLLIB_API Matrix operator*(const Matrix& lhs, const Matrix& rhs) noexcept(false);

		MLLIB_API bool operator==(const Matrix& lhs, const Matrix& rhs) noexcept(false);

		/// <summary>
		/// operator==が定義されているすべての型にoperator!=が自動で定義されます。
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <typeparam name="F"></typeparam>
		/// <param name="a"></param>
		/// <param name="b"></param>
		/// <returns></returns>
		//template<class T, class F = decltype(!(std::declval<T>() == std::declval<T>()))>
		//F operator!=(T a, T b) {
		//	return !(a == b);
		//}

		// テンプレートが使えないので暫定コード
		MLLIB_API inline bool operator!=(const Matrix& lhs, const Matrix& rhs) {
			return !(lhs == rhs);
		}
		
	}
} // myk namespace end

namespace myk {
	using UPtrMtx = std::unique_ptr<lib::Matrix>;
#ifdef _MSC_VER
	using ID = WORD;
#else
	using ID = utin16_t;
#endif
} // myk namespace end


MLLIB_API myk::lib::Matrix GetMatrix(uint32_t, uint32_t);

#ifdef __cplusplus
extern "C" {
#endif
	//extern MLLIB_API int nMlLib;
	//C#側
	MLLIB_API int fnMlLib(void);

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	MLLIB_API myk::ID createNativeMatrix(uint32_t, uint32_t, double);

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	MLLIB_API void deleteNativeMatrix(myk::ID);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	MLLIB_API uint32_t unusedNatMatRelease();

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	MLLIB_API uint32_t unusedNatMatRelease();

	/// <summary>
	/// 
	/// </summary>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <param name=""></param>
	/// <returns></returns>
	MLLIB_API myk::ID initNativeMatrix(double*, int, int, int);
	

	/// <summary>
	/// 
	/// </summary>
	/// <param name="lhs"></param>
	/// <param name="rhs"></param>
	/// <returns></returns>
	MLLIB_API myk::ID nativeDoMultiply(myk::ID, myk::ID);
#ifdef __cplusplus
}
#endif
