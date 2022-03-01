#include <iostream>

class Hoge {
    inline static int count = 0;
    inline static int copycount = 0;
public:
    Hoge() {
        count++;
        std::cout << "Hoge " << count << std::endl;
    }
    Hoge (const Hoge& obj) {
        copycount++;
        std::cout << "Hogeコピーコンストラクタ " << copycount << std::endl;
    }
};

Hoge hoge;

Hoge& sub() {
    return hoge;
}

int main() {
    Hoge& hoge = sub(); //値返しの関数の戻り値を参照型で受けることはできない。
    return 0;
}

