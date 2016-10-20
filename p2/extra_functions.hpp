/**
 * @file extra_functions.hpp
 * @brief <Práctica 2> Funciones extra.
 * @author Eduardo Roldán Pijuán
 * @date Octubre de 2016
 */

#ifndef __EXTRA_FUNCTIONS_HPP__
#define __EXTRA_FUNCTIONS_HPP__

#include <cstdlib>
#include <vector>
#include <cmath>

long double det_rec(const std::vector<std::vector< long double >> matrix, const uint &size){
    long double res = 0, aux = 0;
    int c;
    if(size == 2){
        return matrix[0][0]*matrix[1][1] - matrix[1][0]*matrix[0][1];
    }
    else{
        for( uint i = 0 ; i < size ; ++i ){
            std::vector<std::vector< long double > > m;
            m = std::vector< std::vector< long double > >(size-1, std::vector<long double>(size-1));
            for( uint j = 1 ; j < size ; ++j ){
                c = 0;
                for( uint k = 0 ; k < size ; ++k ){
                    if( k != i ){
                        m[j-1][c] = matrix[j][k];
                        c++;
                    }
                }
            }
            aux = pow(-1, 2+i) * matrix[0][i] * det_rec(m, size-1);
            res += aux;
        }
    }
    return res;
}

#endif
