#include <iostream>
#include <string>

class Fuga {
public:
    Fuga() {
        std::cout << "Fugaのコンストラクタ" << std::endl;
    }
    Fuga(std::string s) {
        std::cout << s + " Fugaのコンストラクタ" << std::endl;
    }
};

class Hoge {
    inline static Fuga hoge = Fuga();
};
