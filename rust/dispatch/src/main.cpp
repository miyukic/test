#include <iostream>
//トレイトクラスを用いたタグディスパッチ

//多態性を持ちたい自作クラス
class Dog{};
class Human{};

//タグ構造体
struct tag_Dog{};
struct tag_Human{};
struct tag_default{};

//トレイトクラス
template<class T>
class traits {
    typedef tag_default tag;
};

//Dog
template<>
struct traits<Dog> {
    typedef tag_Dog tag;
};

//Human
template<>
struct traits<Human> {
    typedef tag_Human tag;
};

//テンプレートグローバル関数をオーバーロードによって静的に呼ぶ
template<class T>
void voice(T& crt, tag_Human) {
    std::cout << "こんにちは" << std::endl;
}

//Dog
template<class T>
void voice(T& crt, tag_Dog) {
    std::cout << "わんわん！" << std::endl;
}

//Human
template<class T>
void voice(T& crt) {
    voice(crt, typename traits<T>::tag());
}

//オブジェクトを受け取る関数
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
