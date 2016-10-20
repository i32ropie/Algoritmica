
#include <iostream>
#include <vector>
#include "main.hpp"

int main(int argc, char const *argv[]) {
    int m = atoi(argv[1]);
    hanoi(m);
//    int n = atoi(argv[1]), k = atoi(argv[2]);
//    std::vector<std::vector< int > > v;
//    v = std::vector<std::vector< int > >(n, std::vector<int>(k));
//    for( int i = 0 ; i < n ; ++i ){
//        for( int j = 0 ; j < k ; ++j )
//            v[i][j] = -1;
//    }
//    std::cout << "(" << n << "," << k << ") = " << combinatorio_iterativo(n, k) << std::endl;
//    std::cout << "(" << n << "," << k << ") = " << combinatorio_recursivo(n, k) << std::endl;
//    std::cout << "(" << n << "," << k << ") = " << combinatorio_recursivo_2(n, k, v) << std::endl;
    return 0;
}
