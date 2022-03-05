// MlLib.cpp : DLL 用にエクスポートされる関数を定義します。
//
#include "pch.h"
#include "framework.h"
#include "MlLib.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <memory>
#include <algorithm>
#include <exception>

#ifndef DBG
#if _DEBUG
#	define DBG(...) std::cout << #__VA_ARGS__ << " = " << [&](){ return __VA_ARGS__; }() << std::endl;
#	define _PRINT(...) std::cout << __VA_ARGS__ << std::endl;
#	define COMPILE_SOURCE_TIME() _PRINT("DATE: " << __DATE__ << "TIME: " << __TIME__)
#	define COMPILE_SOURCE_LOCATION() _PRINT("\nFILE: " << __FILE__ << "LINE: " << __LINE__ << "Func" << __func__)
#	define PRINT(x) COMPILE_SOURCE_ ## x ## ()
#else
#	define DBG(...)
#	define _PRINT(...)
#	define COMPILE_SOURCE_TIME()
#	define COMPILE_SOURCE_LOCATION()
#	define PRINT(x)
#endif
#endif
#ifndef _2DIMENSIONAL_ARRAY
#define _2DIMENSIONAL_ARRAY(array, culum_width, x, y) [&]()->double{ return array[(x)*(culum_width) + (y)]; }()
#endif


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
        const char* hazime = "{";
        const char* owari = "}";
        const char* margin = " ";
        //#endif
        static constexpr uint8_t CAP = 6 * 10;
        std::stringstream sst;
        sst << "\n"
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
            if (matrix.at(i).size() != CUL) {
                throw "Matrixの列サイズが一致していません。";
                return false;
            }
        }
        return true;
    }

    uint32_t Matrix::test() {
        return 321 * 42 + 12 * 3;
    }

#pragma endregion // Matrixクラス

#pragma region Matrixクラスに関するグローバル関数
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

    // 行列同士の加算
    Matrix add(const Matrix& lhs, const Matrix& rhs) noexcept(false) {
        using namespace std::literals::string_literals;
        if (lhs.ROW != rhs.ROW || lhs.CUL != rhs.CUL) {
            throw "計算できない行列です。\n左辺の行と右辺の列が一致している必要があります。\n"s
                + "左辺 Matrix row = "s + std::to_string(lhs.ROW) + "cul = "s + std::to_string(lhs.CUL)
                + "右辺 Matrix row = "s + std::to_string(rhs.ROW) + "cul = "s + std::to_string(rhs.CUL);
        }
        Matrix newMatrix(lhs.ROW, lhs.CUL);
        for (size_t i = 0; i < lhs.ROW; ++i) {
            for (size_t j = 0; j < lhs.CUL; ++j) {
                newMatrix.at(i, j) = lhs.read(i, j) + rhs.read(i, j);
            }
        }
        return newMatrix;
    }

    Matrix operator*(const Matrix& lhs, const Matrix& rhs) noexcept(false) {
        return multiply(lhs, rhs);
    }

    Matrix myk::lib::operator+(const Matrix& lhs, double rhs) noexcept(false) {
        return add(lhs, rhs);
    }

    Matrix myk::lib::operator+(const Matrix& lhs, const Matrix& rhs) noexcept(false) {
        return add(lhs, rhs);
    }

    bool operator==(const Matrix& lhs, const Matrix& rhs) {
        //shapeチェック
        if (lhs.CUL != rhs.CUL || lhs.ROW != rhs.ROW) return false;
        for (size_t i = 0; i < lhs.ROW; ++i) {
            for (size_t j = 0; j < lhs.CUL; ++j) {
                //全要素チェック
                try {
                    if (lhs.read(i, j) != rhs.read(i, j)) return false;
                } catch (std::out_of_range& e) {
                    std::cerr <<
                        "operator==(const Matrix&, const Matrix&)で例外が発生しました。:" <<
                        e.what() << std::endl;
                    //return false;
                }
            }
        }
        return true;
    }
#pragma endregion //Matrixクラスに関するグローバル関数

} //namespace end myk::lib
namespace myk {
    using namespace lib;

    /// <summary>
    /// MatrixオブジェクトをIDと紐づけて管理するクラス。
    /// MatrinxオブジェクトにアクセスするときはIDが必要。(デリート、取得など）
    /// Matrixオブジェクトは UPtrMtx として管理しています。Matrixのunique_ptrです。
    /// Singleton クラス なので ManageMTXObj& getIncetance() で取得。
    /// </summary>
    class ManageMTXObj {
        std::vector<ID> _deletedNum;
        std::vector<UPtrMtx> _mtxList;
        static constexpr uint16_t _MATRIX_QUANTITY = 0x0080;
        static ManageMTXObj _instance;

    public:
        /// <summary>
        /// ManageMTXObj を返す。
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
        static ManageMTXObj& getInstance() {
            return _instance;
        }

        /// <summary>
        /// Matrixオブジェクトを登録
        /// 戻り値は管理用のID
        /// </summary>
        /// <param name="matrix"></param>
        /// <returns></returns>
        ID registMTXObj(UPtrMtx&& matrix) {
            if (_deletedNum.size() > 0) {
                ID id = static_cast<ID>(_deletedNum.size());
                _mtxList.at(id) = std::move(matrix);
                _deletedNum.pop_back();
                return id;
            }
            ID id = static_cast<ID>(_mtxList.size());
            _mtxList.emplace_back(std::move(matrix));
            return id;
        }

        /// <summary>
        /// IDでMatrixオブジェクトを無効にする。
        /// </summary>
        /// <param name=""></param>
        /// <returns></returns>
        void invalidMTXObj(ID id) noexcept(true) {
            auto i = std::find(_deletedNum.begin(), _deletedNum.end(), id);
            if (i == _deletedNum.end())
                _deletedNum.emplace_back(id);
        }

        /// <summary>
        /// 使っていない不要な行列を削除する。
        /// 解放に成功したMatrixオブジェクトの個数を返す。
        /// </summary>
        uint32_t memoryRelease() {
            uint32_t c = 0;
            for (ID id : _deletedNum) {
                if (id <= _mtxList.size()) {
                    _mtxList.at(id).release();
                    ++c;
                } else {
                    continue;
                }
            }
            return c;
        }

        /// <summary>
        /// IDでMatrixオブジェクトの参照を取得
        /// オブジェクトの参照を取得後にregistMTXObj(UPtrMtx)メソッド等で
        /// Matrixオブジェクトを追加するとメモリの再配置により参照が無効になる可能性に注意。
        /// <param name="id"></param>
        /// </summary>
        UPtrMtx& getUPtrMtx(ID id) {
            return _mtxList.at(id);
        }

        ManageMTXObj(const ManageMTXObj&) = delete;
        ManageMTXObj& operator=(const ManageMTXObj&) = delete;
        ManageMTXObj(ManageMTXObj&&) = delete;
        ManageMTXObj& operator=(ManageMTXObj&&) = delete;
    private:
        // コンストラクタ
        ManageMTXObj() { _mtxList.reserve(_MATRIX_QUANTITY); }
        ~ManageMTXObj() = default;
    };
    ManageMTXObj ManageMTXObj::_instance;

#pragma region UPtrMtx関係のグローバル関数
    // 行列積
    myk::UPtrMtx multiply(const UPtrMtx& lhs, const UPtrMtx& rhs) noexcept(false) {
        using namespace std::literals::string_literals;
        if (lhs->CUL != rhs->ROW) {
            throw "計算できない行列です。\n左辺の行と右辺の列が一致している必要があります。\n"s
                + "左辺 Matrix row = "s + std::to_string(lhs->ROW) + "cul = "s + std::to_string(lhs->CUL)
                + "右辺 Matrix row = "s + std::to_string(rhs->ROW) + "cul = "s + std::to_string(rhs->CUL);
        }
        //std::make_unique<Matrix>(lhs->ROW, rhs->CUL);
        myk::UPtrMtx newMatr = std::make_unique<Matrix>(lhs->ROW, rhs->CUL);
        for (size_t r = 0; r < lhs->ROW; ++r) {
            for (size_t c = 0; c < rhs->CUL; ++c) {
                //    newMatr.at(0, 0) = lhs.read(0, 0) * rhs.read(0, 0) + lhs.read(0, 1) * rhs.read(1, 0);
                for (size_t k = 0; k < lhs->CUL; ++k) {
                    newMatr->at(r, c) += lhs->read(r, k) * rhs->read(k, c);
                }
            }
        }
        return newMatr;
    }

    // スカラー加算
    myk::UPtrMtx add(const myk::UPtrMtx& lhs, double rhs) noexcept(false) {
        //myk::UPtrMtx neUPtrMtx = myk::UPtrMtx(lhs->ROW, lhs->CUL);
        myk::UPtrMtx newMatr = std::make_unique<Matrix>(lhs->ROW, lhs->CUL);
        for (size_t i = 0; i < lhs->ROW; ++i) {
            for (size_t j = 0; j < lhs->CUL; ++j) {
                newMatr->at(i, j) = lhs->read(i, j) + rhs;
            }
        }
        return newMatr;
    }

    // 行列同士の加算
    myk::UPtrMtx add(const myk::UPtrMtx& lhs, const myk::UPtrMtx& rhs) noexcept(false) {
        using namespace std::literals::string_literals;
        if (lhs->ROW != rhs->ROW || lhs->CUL != rhs->CUL) {
            throw "計算できない行列です。\n左辺の行と右辺の列が一致している必要があります。\n"s
                + "左辺 Matrix row = "s + std::to_string(lhs->ROW) + "cul = "s + std::to_string(lhs->CUL)
                + "右辺 Matrix row = "s + std::to_string(rhs->ROW) + "cul = "s + std::to_string(rhs->CUL);
        }
        myk::UPtrMtx newMatr = std::make_unique<Matrix>(lhs->ROW, lhs->CUL);
        for (size_t i = 0; i < lhs->ROW; ++i) {
            for (size_t j = 0; j < lhs->CUL; ++j) {
                newMatr->at(i, j) = lhs->read(i, j) + lhs->read(i, j);
            }
        }
        return newMatr;
    }

    // スカラー加算+演算子
    myk::UPtrMtx operator+(const myk::UPtrMtx& lhs, double rhs) noexcept(false) {
        return add(lhs, rhs);
    }

    // 行列加算
    myk::UPtrMtx operator+(const myk::UPtrMtx& lhs, const myk::UPtrMtx& rhs) noexcept(false) {
        return add(lhs, rhs);
    }

    // 行列積*演算子
    myk::UPtrMtx operator*(const myk::UPtrMtx& lhs, const myk::UPtrMtx& rhs) noexcept(false) {
        return multiply(lhs, rhs);
    }
#pragma region //UPtrMtx関係のグローバル関数
} // namespace myk end

namespace myk {
    inline namespace test {
        myk::lib::Matrix getMatrix(uint32_t ROW, uint32_t CUL) {
            return myk::lib::Matrix(ROW, CUL);
        }
    }
}

void getCsObject(CsObject* obj) {
    obj->x = 10;
}

int* getArray() {
    int t[] = {1, 2, 3, 4, 10};
    int* arr = new int[5];
    for (size_t i = 0; i < 5; ++i) {
        arr[i] = t[i];
    }
    return arr;
}

Info info = { 333, "あいうえお", {2, 3, 4, 10}, new int[30]};

Info* getInfoStruct() {
    for (size_t i = 0; i < 30; ++i) {
        info.array[i] = i;
    }
    return &info;
}




myk::lib::Matrix getMatrix(uint32_t ROW, uint32_t CUL) {
    return myk::lib::Matrix(ROW, CUL);
}

#pragma endregion


#pragma region FFI API

// これは、エクスポートされた変数の例です
//MLLIB_API int nMlLib=0;

// これは、エクスポートされた関数の例です。
int fnMlLib(void) {
    std::cout << "fnMlLiv が実行されました" << std::endl;
    return 100 * 3;
}

// Matrixオブジェクトを生成しidを返す。
myk::ID createNativeMatrixRCV(uint32_t ROW, uint32_t CUL, double value) {
    DBG(ROW);
    DBG(CUL);
    DBG(value);
    using namespace myk;
    auto mtx = std::make_unique<lib::Matrix>(ROW, CUL, value);
    ManageMTXObj& mmo = myk::ManageMTXObj::getInstance();
    ID id = mmo.registMTXObj(std::move(mtx));
    return id;
}

// idのMatrixオブジェクトを無効にする。
void deleteNativeMatrix(myk::ID id) {
    using namespace myk;
    ManageMTXObj& mmo = ManageMTXObj::getInstance();
    mmo.invalidMTXObj(id);
}

// 不要な行列を削除する
uint32_t unusedNatMatRelease() {
    using namespace myk;
    ManageMTXObj& mmo = ManageMTXObj::getInstance();
    return mmo.memoryRelease();
}

myk::ID createNativeMatrixARC(double* arr, uint32_t len, uint32_t ROW, uint32_t CUL) {
    using namespace myk;
    std::vector<std::vector<double>> vec(ROW, std::vector<double>(CUL));
    for (size_t r = 0; r < ROW; ++r) {
        for (size_t c = 0; c < CUL; ++c) {
            vec.at(r).at(c) = _2DIMENSIONAL_ARRAY(arr, CUL, r, c);
        }
    }
    auto mtx = std::make_unique<lib::Matrix>(vec);
    ManageMTXObj& mmo = myk::ManageMTXObj::getInstance();
    ID id = mmo.registMTXObj(std::move(mtx));
    return id;
}

// 行列積を実行
myk::ID nativeMatrixMultiply(myk::ID lhs, myk::ID rhs) {
    using namespace myk::lib;
    using namespace myk;
    myk::ManageMTXObj& mmo = myk::ManageMTXObj::getInstance();
    myk::UPtrMtx& upmL = mmo.getUPtrMtx(lhs);
    myk::UPtrMtx& upmR = mmo.getUPtrMtx(rhs);
    try {
        myk::UPtrMtx mtx = upmL * upmR;
        return mmo.registMTXObj(std::move(mtx));
    } catch (const char* msg) {
        std::cerr << "nativeMatrixMultiply() 関数 " << (__LINE__) -3 << "行目\n"
            << msg << std::endl;
        return 0;
    } catch (std::exception& e) {
        std::cerr << "nativeMatrixMultiply() 関数 " << (__LINE__) -6 << "行目\n"
            << e.what() << std::endl;
        return 0;
    }
}

//スカラー値を加算
myk::ID nativeMatrixAddSC(myk::ID lId, double value) {
    using namespace myk::lib;
    using namespace myk;
    myk::ManageMTXObj& mmo = myk::ManageMTXObj::getInstance();
    myk::UPtrMtx& upm = mmo.getUPtrMtx(lId);
    return mmo.registMTXObj(add(upm, value));
}

uint32_t getROW(myk::ID id) {
    using namespace myk;
    ManageMTXObj& mmo = ManageMTXObj::getInstance();
    return mmo.getUPtrMtx(id)->ROW;
}

uint32_t getCUL(myk::ID id) {
    using namespace myk;
    ManageMTXObj& mmo = ManageMTXObj::getInstance();
    return mmo.getUPtrMtx(id)->CUL;
}

BOOL nativeMatrixPrint(myk::ID id) {
    using namespace myk;
    try {
        ManageMTXObj::getInstance().getUPtrMtx(id)->print();
    } catch (std::exception e) {
        DBG("nativeMatrixPrint(myk::ID)", e.what())
            PRINT(TIME);
        PRINT(LOCATION);
        return false;
    }
    return true;
}

BOOL nativeMatrixEquals(myk::ID lhs, myk::ID rhs) {
    using namespace myk::lib;
    using namespace myk;
    myk::ManageMTXObj& mmo = myk::ManageMTXObj::getInstance();
    myk::UPtrMtx& l = mmo.getUPtrMtx(lhs);
    myk::UPtrMtx& r = mmo.getUPtrMtx(rhs);
    return (*l) == (*r);
}

myk::ID nativeMatrixAdd(myk::ID lhs, myk::ID rhs) {
    using namespace myk::lib;
    using namespace myk;
    ManageMTXObj& mmo = myk::ManageMTXObj::getInstance();
    UPtrMtx& l = mmo.getUPtrMtx(lhs);
    UPtrMtx& r = mmo.getUPtrMtx(rhs);
    ID id = mmo.registMTXObj(std::move(add(l, r)));
    return id;
}


#pragma endregion //FFI API

