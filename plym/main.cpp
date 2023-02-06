#include <iostream>
#include <memory>

class ITag { 
    virtual void f() = 0;
};

class Base {
    virtual void g() = 0;
};

class Sub : public Base, public ITag {
public:
    void f() override {
        std::cout << "Sub#f\n";
    } 
    void g() override {
        std::cout << "Sub#g\n";
    } 
};

template<class U, class T>
std::unique_ptr<U> dynamic_unique_cast(std::unique_ptr<T> &&ptr) {
    return std::unique_ptr<U>{dynamic_cast<U*>(ptr.release())};
}

int main() {
    auto base = std::make_unique<Sub>(); 

    std::unique_ptr<ITag> o = std::move(base);

    if (auto a = dynamic_unique_cast<Sub>(std::move(o))) {
        a->f();
        a->g();
        std::cout << "OK\n";
    } else {
        std::cout << "NO\n";
    }
}
