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
#ifndef _WINDOWS
typedef int BOOL;
#endif // !_WINDOWS

#pragma once
#include <vector>
#include <initializer_list>
#include <string>
#include <memory>

struct MLLIB_API CsObject {
    int x;
    int y;
};

struct MLLIB_API Info {
    int    index;
    char   name[128];
    int    statuses[50];
};

extern "C" {
    MLLIB_API void getCsObject(CsObject* obj);
    MLLIB_API int* getArray();
    MLLIB_API Info* getInfoStruct();
}

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
            Matrix(Matrix&& from) noexcept;


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

        MLLIB_API Matrix operator+(const Matrix& lhs, double rhs) noexcept(false);

        MLLIB_API Matrix operator+(const Matrix& lhs, const Matrix& rhs) noexcept(false);

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

    } // ::lib namespace end
} // myk namespace end

namespace myk {
    using UPtrMtx = std::unique_ptr<lib::Matrix>;
#ifdef _MSC_VER
#	ifdef WORD
    using ID = WORD;
#	else
#	include <limits.h>
#	if USHRT_MAX == 0xFFFF 
    using ID = unsigned short;
#	endif
#	endif
#else
    using ID = uint16_t;
#endif

    MLLIB_API UPtrMtx multiply(const UPtrMtx& lhs, const UPtrMtx& rhs) noexcept(false);

    MLLIB_API UPtrMtx add(const UPtrMtx& lhs, double rhs) noexcept(false);

    // 行列同士の加算計算
    MLLIB_API UPtrMtx add(const UPtrMtx& lhs, const UPtrMtx& rhs) noexcept(false);

    MLLIB_API UPtrMtx operator*(const UPtrMtx& lhs, const  UPtrMtx& rhs) noexcept(false);

    MLLIB_API UPtrMtx operator+(const UPtrMtx& lhs, double rhs) noexcept(false);

    MLLIB_API UPtrMtx operator+(const UPtrMtx& lhs, const UPtrMtx& rhs) noexcept(false);
} // myk namespace end


MLLIB_API myk::lib::Matrix GetMatrix(uint32_t, uint32_t);

#ifdef __cplusplus
extern "C" {
#endif
    //extern MLLIB_API int nMlLib;
    //C#側
    MLLIB_API int fnMlLib(void);

    /// <summary>
    /// 行と列と値を指定して行列を作成。
    /// 行列のIDを返す。
    /// </summary>
    /// <param name="">行</param>
    /// <param name="">列</param>
    /// <param name="">初期値</param>
    /// <returns>行列オブジェクトのID</returns>
    MLLIB_API myk::ID createNativeMatrixRCV(uint32_t, uint32_t, double);

    /// <summary>
    /// IDを指定して行列を削除
    /// </summary>
    /// <param name=""></param>
    MLLIB_API void deleteNativeMatrix(myk::ID);

    /// <summary>
    /// 使用していない行列をメモリから削除する。
    /// </summary>
    /// <returns>削除した行列の数</returns>
    MLLIB_API uint32_t unusedNatMatRelease();

    /// <summary>
    /// </summary>
    /// <param name="">行列を初期化する一次元配列</param>
    /// <param name="">使われてない</param>
    /// <param name="">行</param>
    /// <param name="">列</param>
    /// <returns></returns>
    MLLIB_API myk::ID createNativeMatrixARC(double*, uint32_t, uint32_t, uint32_t);

    /// <summary>
    /// 行列積を計算し結果の行列のIDを返す
    /// </summary>
    /// <param name="lhs"></param>
    /// <param name="rhs"></param>
    /// <returns>行列オブジェクトのID</returns>
    MLLIB_API myk::ID nativeMatrixMultiply(myk::ID, myk::ID);

    /// <summary>
    /// 行列にスカラー値を加算します。
    /// </summary>
    /// <param name="lId"></param>
    /// <param name="value"></param>
    /// <returns>行列オブジェクトのID</returns>
    MLLIB_API myk::ID nativeMatrixAddSC(myk::ID, double);

    /// <summary>
    /// IDの行を取得
    /// </summary>
    /// <param name="id"></param>
    /// <returns></returns>
    MLLIB_API uint32_t getROW(myk::ID id);

    /// <summary>
    /// IDの列を取得
    /// </summary>
    /// <param name="id"></param>
    /// <returns></returns>
    MLLIB_API uint32_t getCUL(myk::ID id);

    /// <summary>
    /// IDを指定し行列の内容を標準出力する。
    /// </summary>
    /// <param name="id"></param>
    /// <returns></returns>
    MLLIB_API BOOL matrixConsoleOutPut(myk::ID id);

    /// <summary>
    /// IDを指定し行列を比較する
    /// </summary>
    /// <param name="lhs"></param>
    /// <param name="rhs"></param>
    MLLIB_API BOOL nativeMatrixEquals(myk::ID lhs, myk::ID rhs);

    /// <summary>
    /// 行列同士で加算する
    /// </summary>
    /// <param name="lhs"></param>
    /// <param name="rhs"></param>
    MLLIB_API myk::ID nativeMatrixAdd(myk::ID lhs, myk::ID rhs);
#ifdef __cplusplus
}
#endif
