#include <iostream>
#include <memory>

class Base {
    inline static const char[] name = "Base";
public:
    inline virtual void f() noexcept {
        std::cout << "base" << "\n" << std::flush;
    }
};

class Sub : public Base {
public:
    inline void f() noexcept override {
        std::cout << "Sub" << "\n" << std::flush;
    }
};


int main() {
    std::unique_ptr<Base> sub = std::make_unique<Sub>();
    auto& sub2 = sub;
    sub->f();
    sub2->f();
    //Sub base = static_cast<Sub>(Base());
}
