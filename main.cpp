#include <iostream>


uint32_t add(const uint32_t&, const uint32_t&);
uint32_t sub(const uint32_t&, const uint32_t&);

bool hAdd(const uint8_t&, const uint8_t&, uint8_t&, uint8_t&); 
bool fAdd(const uint8_t&, const uint8_t&, const uint8_t&, uint8_t&, uint8_t&); 

int main() {
    //std::cout << "add(3, 5)=" << add(3, 5) << std::endl;
    //std::cout << "sub(10, 5)=" << sub(323, 5) << std::endl;
}

uint32_t add(const uint32_t &a, const uint32_t &b) {
    return a + b;    
}

uint32_t sub(const uint32_t &a, const uint32_t &b) {
    uint32_t t = ~b;
    t++;
    return add(a, t);
}

bool hAdd(const uint8_t& a,
        const uint8_t& b,
        uint8_t &result,
        uint8_t &carry) {
    bool bl = false;
    bl |= a > 1;
    bl |= b > 1;
    result = a ^ b;
    return !bl;
} 

bool fAdd(const uint8_t &a,
        const uint8_t &b,
        const uint8_t &c,
        uint8_t &result,
        uint8_t &carry) {
    //if (a > 1 || b > 1 || c > 1) return false;
    bool bl = false;
    bl |= a > 1;
    bl |= b > 1;
    bl |= c > 1;

    return !bl;
}

