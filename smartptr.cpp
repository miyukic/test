#include <iostream>
#include <memory>

class Hoge {

  public:
    Hoge() {
        std::cout << "Hogeのコンストラクタが呼ばれた" << std::endl;
    }

    ~Hoge() {
        std::cout << "Hogeのデストラクタが呼ばれた" << std::endl;
    }
    
    Hoge(const Hoge &obj) {
        std::cout << "Hogeのコピーコンストラクタが呼び出されました" << std::endl;
    }

    Hoge(Hoge &&from) {
        std::cout << "Hogeのムーブコンストラクタ" << std::endl;
    }

};

class HogeGen {

  public:
    static std::unique_ptr<Hoge> getHoge() {
        auto a = std::unique_ptr<Hoge>(new Hoge());
        return move(a);
    }

    

};

std::unique_ptr<Hoge> sub() {
    std::unique_ptr<Hoge> hoge = HogeGen::getHoge(); //hogeにムーブ
    return move(hoge);
}

Hoge& recieve(Hoge &obj) {
    return obj;
}

int main() {
    auto a = sub();
    std::unique_ptr<Hoge> h = std::move(a);
    auto c = std::move(h);
    //Hoge h1 = Hoge();
    //Hoge h2 = h1;
    std::cout << "main終了\n";
    return 0;
}

