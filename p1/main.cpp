#include <iostream>
#include "matrix.hpp"
#include "main.hpp"

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    uint size = argc==2?atoi(argv[1]):5;
    al::Matrix matrix(size);
    // matrix.print_matrix();
    std::cout << "Determinante de matriz " << size << "x" << size << " : " << det(matrix) << std::endl;
    return 0;
}
