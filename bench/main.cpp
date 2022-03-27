#include <array>
#include <vector>
#include <random>
#include <iostream>
#include <chrono>


constexpr int32_t SIZE = 500;
std::array<double, SIZE*SIZE> multiply(const std::array<double, SIZE*SIZE>& lhs, const std::array<double, SIZE*SIZE>& rhs) noexcept(false) {
        int lCUL = SIZE;
        int rROW = SIZE;
        int rCUL = SIZE;
        int lROW = SIZE;
        std::array<double, SIZE*SIZE> newMatr;
        for (int r = 0; r < lROW; ++r) {
            for (int c = 0; c < rCUL; ++c) {
                for (int k = 0; k < lCUL; ++k) {
                    newMatr.at(r * rCUL + c) += lhs.at(r * lROW + k) * rhs.at(k * rCUL + c);
                }
            }
        }
        return newMatr;
}


int main() {
std::cout << "開始" << std::endl;
	std::random_device seed_gen;
	std::mt19937 engine{seed_gen()};
	std::uniform_real_distribution<> dist{0, 50};


    std::cout << "配列初期化開始" << "SIZE = " << SIZE << std::endl;
    std::array<double, SIZE*SIZE> array;
    for (int32_t i = 0; i < SIZE; ++i) {
        for (int32_t j = 0; j < SIZE; ++j) {
            array.at(i*SIZE + j) = dist(engine);
        }
    }
    std::cout << "配列初期化終了" << std::endl;
    std::chrono::system_clock::time_point start, end;

    start = std::chrono::system_clock::now();
    auto ret = ::multiply(array, array);
    end = std::chrono::system_clock::now();
    double resultTime = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
    std::cout << "経過時間(ms) " << resultTime << std::endl;

    //for (int row = 0; row < SIZE; ++row) {
    //    for (int clm = 0; clm < SIZE; ++clm) {
    //        std::cout << ret.at(row * SIZE + clm) << " ";
    //    }
    //    std::cout << "\n";
    //}
    //std::cout << std::flush;
    return 0;
}
