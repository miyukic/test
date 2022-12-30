#include <iostream>

class Dog{};
class Human{};

struct tag_Dog{};
struct tag_Human{};
struct tag_default{};

template<class T>
class traits {
    typedef tag_default tag;
};

template<>
struct traits<Dog> {
    typedef tag_Dog tag;
};

template<>
struct traits<Human> {
    typedef tag_Human tag;
};

template<class T>
void voice(T& crt, tag_Human) {
    std::cout << "こんにちは" << std::endl;
}

template<class T>
void voice(T& crt, tag_Dog) {
    std::cout << "わんわん！" << std::endl;
}

template<class T>
void voice(T& crt) {
    voice(crt, typename traits<T>::tag());
}

template<class T>
void f(T& crt) {
    voice(crt);
}

int main() {
    auto human = Human{};
    auto dog = Dog{};

    f(human);
    f(dog);
}
