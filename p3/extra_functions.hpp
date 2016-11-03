//
// Created by i32ropie on 29/10/16.
//

#ifndef P3_EXTRA_FUNCTIONS_HPP
#define P3_EXTRA_FUNCTIONS_HPP

#include <cstdlib>
#include <vector>
#include <cmath>
#include <algorithm>

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

//std::vector<int> string_to_vector(std::string a){
//    std::vector<int> b;
//    std::reverse(a.begin(), a.end());
//    for(auto it = a.begin() ; it != a.end() ; ++it){
//        char c = *it;
//        b.push_back(atoi(&c));
//    }
//    return b;
//}
//
bool is_int(const std::string & s) {
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false ;
    char * p ;
    strtol(s.c_str(), &p, 10) ;
    return (*p == 0) ;
}


#endif //P3_EXTRA_FUNCTIONS_HPP
