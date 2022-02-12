#include <string>

class Console {
    const static std::string ESC;
    //int** mMap = new int*[10];
    int* map[10] = {};
public:
    static void clear();

    static void moveCursor(const int row, const int colum);

    static void hideCursor();
}; 
