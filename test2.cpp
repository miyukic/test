#include <iostream>
#include <string>

class Hoge {
    static Hoge _instance;
public:
    std::string name = "Hoge";
    static Hoge& getInstance() {
        //if (_instance == nullptr) {
        //    _instance = new Hoge();
        //}
        //return _instance;
        return _instance;
    }

};

int main() {
    Hoge& hoge = Hoge::getInstance();
    std::cout << hoge.name;
    return 0;
}

