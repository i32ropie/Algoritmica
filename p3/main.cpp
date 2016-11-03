#include <iostream>
#include "entero.hpp"

int main() {
    al::Entero entero1, entero2;
    std::cin >> entero1;
//    std::cout << std::endl;
    std::cin >> entero2;
    std::cout << std::endl;
    std::cout << entero1 << " * " << entero2 << " = " << entero1 * entero2 << std::endl;
    return 0;
}