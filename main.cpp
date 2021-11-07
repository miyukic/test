#include <iostream>


inline uint32_t add(const uint32_t&, const uint32_t&);
inline uint32_t sub(const uint32_t&, const uint32_t&);

int main() {
    //std::cout << "add(3, 5)=" << add(3, 5) << std::endl;
    //std::cout << "sub(10, 5)=" << sub(323, 5) << std::endl;
}

inline uint32_t add(const uint32_t &a, const uint32_t &b) {
    return a + b;    
}

inline uint32_t sub(const uint32_t &a, const uint32_t &b) {
    uint32_t t = ~b;
    t++;
    return add(a, t);
}
