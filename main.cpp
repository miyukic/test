#include <Windows.h>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Base {
public:
    int a = 0;
    virtual ~Base() {}
    void virtual baseFunc() {
        std::cout << "Base#baseFunc()\n";
    }
};

class Sub : public Base {
    public:
    int b = 0;
    void baseFunc() override {
        std::cout << "Sub#baseFunc()\n";
    }
    void subFunc() {
        std::cout << "Sub#subFunc()" << this->b << "\n";
    }
};

class Other {
public:
    void baseFunc() {
        std::cout << "Other#baseFunc()\n";
    }
    void subFunc() {
        std::cout << "Other#subFunc()\n";
    }
};

int main(/*int argc, char* argv[]*/) {
    std::string s = "hogehoge";
    std::istringstream istm(s);
    std::cout << s << std::endl;
    Base* b = new Sub{};
    b->baseFunc();

    try {
        Sub& sub = dynamic_cast<Sub&>(*b);
        sub.baseFunc();
        sub.subFunc();
    } catch (std::bad_exception& e) {
        std::cout << e.what() << std::endl;
    }
    //if (sub == nullptr) {
    //    std::cout << "nullptr\n";
    //}
    //auto& ifs = dynamic_cast<std::ifstream&>(istm);
    //if (&ifs == nullptr) {
    //    std::cout << "nullでした。\n";
    //} else {
    //    std::cout << "nullではありません。\n";
    //}
}

