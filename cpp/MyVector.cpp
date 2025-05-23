/*
#include <iostream>
#include "MyVector.hpp"

int main() {
    MyVector<bool> vb;
    vb.push_back(true);   // [1]
    vb.push_back(false);  // [1, 0]
    vb.push_back(true);   // [1, 0, 1]
    vb[1] = true;         // [1, 1, 1]
    vb.insert(1, false);  // [1, 0, 1, 1]
    vb.erase(0);          // [0, 1, 1]

    for (size_t i = 0; i < vb.size_b(); ++i) {
        std::cout << vb[i] << " "; // Вывод: 0 1 1
    }
}
*/