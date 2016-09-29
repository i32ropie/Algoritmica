#ifndef __EXTRA_FUNCTIONS_HPP__
#define __EXTRA_FUNCTIONS_HPP__

#include <cstdlib>

double get_random_number(){
    double negative = false;
    if(rand()%2) negative = true;
    double rand_number = double(rand()%(100000+1))/10000;
    // double rand_number = double(rand()%10+1);
    return negative?-1*rand_number:rand_number;
}

#endif
