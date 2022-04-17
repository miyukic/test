#include <ios>
#include <iostream>
#include <random>
#include <memory>
#include <cstring>
#include <concepts>
#include <stdlib.h>
#include <cstdlib>


namespace myk {
    inline void panic(const std::string& msg = "The panic function was called") {
        std::cerr << msg << std::endl;
        std::exit(1);
    }
    
    namespace util {
        template<class T, class WHY>
        union Data {
            T Ok;
            WHY Err;
        };

        enum class Result {
            OK,
            ERR,
        };
    }

    template<class OK, class WHY>
    struct Result {
        constexpr Result(util::Result result, util::Data<OK, WHY> data)
            : _data{data} {
            _result = result;
        }
        constexpr OK& value() & {
            if(_result == util::Result::OK) {
                return _data.Ok;
            } else {
                panic();
            }
        }
        constexpr const OK& value() const& {
            if(_result == util::Result::OK) {
                return _data.Ok;
            } else {
                panic();
            }
        }
        constexpr OK&& value() && {
            if(_result == util::Result::OK) {
                return std::move(_data.Ok);
            } else {
                panic();
            }
        }
        constexpr const OK&& value() const&& {
            if(_result == util::Result::OK) {
                return std::move(_data.Ok);
            } else {
                panic();
            }
        }

        constexpr explicit operator bool() const noexcept {
            return _result == util::Result::OK;
        }
    private:
        util::Data<OK, WHY> _data;
        util::Result        _result;
    };
}

template<class T>
concept Comparable = std::integral<T> || std::floating_point<T>;

template<Comparable T = double, std::unsigned_integral U = uint32_t> class Matrix;
template<Comparable T, std::unsigned_integral U>
struct Matrix {
    Matrix(U row, U clm): _matrix{new T[row*clm]}, _ROW{row}, _CLM{clm} {}

    Matrix(Matrix&& other) : _ROW{other._ROW}, _CLM{other._CLM}, _matrix{other._matrix} {
        other._matrix = nullptr;
    }

    Matrix(const Matrix& other) : _ROW{other._ROW}, _CLM{other._CLM}, _matrix{new T[other._row * other._clm]} {
        std::memcpy(_matrix, other._matrix, sizeof(_matrix));
    }

    ~Matrix() {
        delete[] _matrix;
    }

    T read(U row, U clm) const {
        return _matrix[clm + row * _CLM];
    }

    T& at(U row, U clm) {
        return _matrix[clm + row * _CLM];
    }

    U getClm() const {
        return _CLM;
    } 

    U getRow() const {
        return _ROW;
    }
private:
    T *_matrix;
    const U _ROW;
    const U _CLM;
};

template<Comparable T, Comparable U>
myk::Result<Matrix<T, U>, std::string> operator*(Matrix<T, U> lhs, Matrix<T, U> rhs) noexcept {
    using namespace myk;
    U lCLM = lhs.getClm();
    U rROW = rhs.getRow();
    if (lCLM != rROW) {
        return Result<Matrix<T, U>, std::string>();
    }

    U rCLM = rhs.getClm();
    U lROW = lhs.getRow();
    auto newMat = Matrix<T, U>{};

    return newMat;
}

int main() {
    auto mtx = Matrix<>(32, 32);
    auto r = mtx.getClm();
    return 0;
}
