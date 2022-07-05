#include <iostream>


int main(int argc, char* argv[]) {
    //std::cout << argc << std::endl;
    if ( argc >= 2 ) {
        std::cout << argv[1][1] << std::endl;
    }
    int a[5] = {1, 2, 3, 4, 5};
    std::cout << *1[&a] << std::endl; //1が表示される
    std::cout << 0[a] << std::endl; //1が表示される
    // std::cout << *(0 + 1); //1が表示される
    // std::cout << **(0 + 1); //1が表示される
    std::cout << *(*(&a) + 0) << std::endl;　//2
    std::cout << *(0[&a] + 0) << std::endl;   //2
}

