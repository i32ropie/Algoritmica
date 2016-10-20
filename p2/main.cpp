
#include <iostream>
#include <vector>
#include "main.hpp"
#include "hanoi.hpp"


int main(int argc, char const *argv[]) {
    int m = atoi(argv[1]);
    al::Hanoi h(m);
    cls();
    std::cout << std::endl << std::endl << h << std::endl << "Estado inicial, pulsa ENTER para continuar";
    std::cin.ignore();
    sleep(2);
    h.solve_hanoi(true);
    std::cout << std::endl << "Hanoi resuelto en " << h.get_moves() << " movimientos." << std::endl;
    return 0;
}
