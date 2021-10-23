#define calc(x, y) ((x) * (y))
#define tozero(z) (0)
#define REP(i,a,b) for (int i = (a); i < b; ++i)
#define dbg(...) std::cout << #__VA_ARGS__ << " = " << [&]{ return __VA_ARGS__; }() << std::endl;



int main() {
    int a = calc(3, 5);
    return tozero(a);
}


