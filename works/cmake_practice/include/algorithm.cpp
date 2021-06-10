#include "algorithm.h"

template<typename T>
T math::add(T num1, T num2) {
    return num1 + num2;
}

template<typename T>
T math::multi(T num1, T num2) {
    return num1 * num2;
}

int math::add_add(int &num) {
    ++num;
    return num;
}