#include <iostream>

#include "../include/algorithm.h"

int main (void) {
    int a = 2, b = 3;
    float c = 2.5, d = 3.5;

    // std::cout<<"2 + 3 = "<<math::add(a, b)<<std::endl;
    // std::cout<<"2 * 3 = "<<math::multi(a, b)<<std::endl;
    // std::cout<<"2.5 + 3.5 = "<<math::add(c, d)<<std::endl;
    // std::cout<<"2 * 3 = "<<math::multi(c, d)<<std::endl;
    std::cout<<"++2 = "<<math::add_add(a)<<std::endl;

    return 0;
}