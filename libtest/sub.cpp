#include <iostream>
#include <string>

using std::string;

string sub() {
    std::cout << "Called sub()" << std::endl;
    string h = "sub.sub()";
    return h;
}

