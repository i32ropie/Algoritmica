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

std::vector<long double> cramer(const uint &params, std::vector<std::vector< long double > > &aux, std::vector< long double > &aux2){
    std::vector<long double> params_value;
    for( int i = 0 ; i < params ; ++i ){
        std::vector<std::vector< long double > > aux3 = aux;
        for( int j = 0 ; j < params ; ++j ){
            aux3[j][i] = aux2[j];
        }
        long double det1 = det_rec(aux3, params), det2 = det_rec(aux, params);
        params_value.push_back(det1/det2);
    }
    return params_value;
}

std::vector<uint> transform_test_size(const std::vector<uint> &test_size, const bool &lineal){
    std::vector<uint> res;
    if(!lineal){
        for( uint i = 0 ; i < test_size.size() ; ++i ){
            res.push_back(pow(2, test_size[i]));
        }
    }
    else{
        res = test_size;
    }
    return res;
}

void indep_terms(const uint &params, const std::vector<uint> &test_size, std::vector<std::vector< long double > > &aux){
    long double tmp;
    int n = test_size.size();
    for( int i = 0 ; i < params ; ++i ){
        for( int j = 0 ; j < params ; ++j ){
            if( i == 0 && j == 0 ){
                aux[i][j] = n;
            }
            else{
                tmp = 0;
                for( int k = 0 ; k < n ; ++k ){
                    tmp += pow(test_size[k], i+j);
                }
                aux[i][j] = tmp;
            }
        }
    }
}

void dep_terms(const uint &params, const std::vector<uint> &test_size, const std::vector<uint64_t> &elapsed_time, std::vector<long double> &aux){
    long double tmp;
    int n = test_size.size();
    for( int i = 0 ; i < params ; ++i ){
        tmp = 0;
        for( int j = 0 ; j < n ; ++j ){
            tmp += pow(test_size[j], i) * elapsed_time[j];
        }
        aux[i] = tmp;
    }
}


#endif
