//https://www.youtube.com/watch?v=to_byzZXBFg
#include <iostream>
#include <bit>


uint32_t add(const uint32_t&, const uint32_t&);
uint32_t sub(const uint32_t&, const uint32_t&);
uint8_t getBit(uint32_t, uint32_t);

bool hAdd(const uint8_t&, const uint8_t&, uint8_t&, uint8_t&); 
bool fAdd(const uint8_t&, const uint8_t&, const uint8_t&, uint8_t&, uint8_t&); 

int main() {
    //std::cout << "add(3, 5)=" << add(3, 5) << std::endl;
    //std::cout << "sub(10, 5)=" << sub(323, 5) << std::endl;

    std::cout << "333 + 214" << add(333, 214) << " = " << 333 + 214 << std::endl;
}

uint32_t add(const uint32_t &a, const uint32_t &b) {
    
    uint8_t sum = 0;            //加算器のsum
    uint8_t carry = 0;          //加算器のcarry
    hAdd(getBit(a, 1), getBit(b, 1), sum, carry);
    uint32_t result = 0;            //すべての桁を足し合わせた結果
    result = sum;
    for (size_t N = 1; N <= std::numeric_limits<uint32_t>::digits; N++) {
        uint8_t return_carry;
        fAdd(carry, getBit(a, N), getBit(b, N), sum, return_carry); 
        result += sum;
        carry = return_carry;
    }

    return result;
    //return a + b;    
}

uint32_t sub(const uint32_t &a, const uint32_t &b) {
    uint32_t t = ~b;
    t++;
    return add(a, t);
}

uint8_t getBit(const uint64_t a, const uint64_t N) {
    return static_cast<uint8_t>((a >> N) & 1ULL);
}

bool hAdd(const uint8_t& a,
        const uint8_t& b,
        uint8_t &result,
        uint8_t &carry) {
    bool bl = false;
    bl |= a > 1;
    bl |= b > 1;
    carry = a & b;
    result = a ^ b;
    return !bl;
} 

bool fAdd(const uint8_t &a,
        const uint8_t &b,
        const uint8_t &c,
        uint8_t &result,
        uint8_t &carry) {
    bool bl = false;
    bl |= a > 1;
    bl |= b > 1;
    bl |= c > 1;
    
    uint8_t c1 = 0;
    uint8_t r_ = 0;
    hAdd(a, b, r_, c1);
    uint8_t c2 = 0;
    hAdd(c, r_, result, c1);

    carry = c1 & c2;
    return !bl;
}

