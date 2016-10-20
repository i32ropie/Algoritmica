#ifndef __MAIN_HPP__
#define __MAIN_HPP__

#include <iostream>
#include <vector>

long long combinatorio_iterativo(const int &n,const int &k){
    long long fact_n = 1, fact_k = 1, fact_nk = 1;
    for( int i = 2 ; i <= n ; ++i )
        fact_n *= i;
    for( int i = 2 ; i <= k ; ++i )
        fact_k *= i;
    for( int i = 2 ; i <= (n-k) ; ++i )
        fact_nk *= i;
    return fact_n/fact_k/fact_nk;
}

int combinatorio_recursivo(const int &n, const int &k){
    if(k == 0 || k == n){
        return 1;
    }
    return combinatorio_recursivo(n-1, k-1) + combinatorio_recursivo(n-1, k);
}

int combinatorio_recursivo_2(const int &n, const int &k, std::vector<std::vector< int > > &aux){
    int a;
    if(k == 0 || k == n)
        return 1;
    if( aux[n-1][k-1] != -1 ){
        a = aux[n-1][k-1];
    }
    else{
        a = combinatorio_recursivo_2(n-1, k-1, aux) + combinatorio_recursivo_2(n-1, k, aux);
        aux[n-1][k-1] = a;
    }
    return a;
}

void hanoi(int m, int i, int j){
    if(m > 0){
        hanoi(m-1, i, 6 - i - j);
        std::cout << "Movemos la pieza superior de " << i << " a " << j << "." << std::endl;
        hanoi(m-1, 6 - i - j, j);
    }
}

#endif
