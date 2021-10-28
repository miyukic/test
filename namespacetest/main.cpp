A#include <iostream>

namespace NS1 {
  namespace NS2 {
    void Hello()
    {
      std::cout << "Hello, world" << std::endl;
    }
  }
}

//! 空の namespace でエラーになる
namespace NS2 {
}

int main()
{
  using namespace NS1;
  NS2::Hello();

  return 0;
}

