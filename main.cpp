#include <iostream>
#include <string>
#include <cstdint>



class Hoge {
   inline static int count = 0;
   inline static int copycount = 0;
public:
   Hoge() {
       count++;
       std::cout << "Hoge " << count << std::endl;
   }
   Hoge (const Hoge& obj) {
       copycount++;
       std::cout << "Hogeコピーコンストラクタ " << copycount << std::endl;
   }
    static bool operator==(const Hoge& rhs) const& {
        return true;
    }
};

//Hoge hoge;


//Hoge& sub() {
//   return hoge;
//}


// struct Sample {
//     std::string username;
//     std::string email;
//     uint64_t signInCount;
//     bool active;
// };

int main() {
}

