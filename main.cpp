#include <iostream>


int main(int argc, char* argv[]) {
    std::cout << argc << std::endl;
    if ( argc >= 2 ) {
        std::cout << argv[1][1] << std::endl;
    }
}

