#include <iostream>
//*#include <string>
//*#include <cstdint>
#include <memory>

//Hogeclass Hoge {
//Hogepublic:
//Hoge    int a = 0;
//Hoge};
//Hoge
//Hoge
//Hogestd::unique_ptr<Hoge> f() {
//Hoge    return std::make_unique<Hoge>();
//Hoge}
//Hoge
//Hogeint main() {
//Hoge    auto a = f();
//Hoge} 

class Hoge {
};

std::unique_ptr<Hoge> hoge() {
    std::unique_ptr<Hoge> p(new Hoge());
    return p;
    //return std::move(make_unique<int>());
}

int main() {
    using namespace std;
    std::unique_ptr<Hoge> hoge = ::hoge();
    return 0;
}

