#include <iostream>
#include <vector>
#include <cstdint>
#include <limits>

void print_ppint(int** nums, int size) {
    for (int i = 0; i < size; i++){
        std::cout<<(*nums)[i]<<" ";
    }
    std::cout<<std::endl;
}

void print_p_c_pint(int* const * nums, int size) {
    for (int i = 0; i < size; i++){
        std::cout<<(*nums)[i]<<" ";
    }
    std::cout<<std::endl;
}

int main (void) {
    // std::cout<<"hello world!"<<std::endl;
    // std::vector<float> a(3, std::numeric_limits<float>::max());
    // for(int i = 0; i < a.size(); i++) std::cout<<a[i]<<std::endl;
    
    int* nums = new int[3];
    int* nums_2 = new int[3];

    for (int i = 0; i < 3; i++) nums[i] = i;
    for (int i = 0; i < 3; i++) nums_2[i] = i + 5;

    int** pp_nums = &nums;
    print_ppint(pp_nums, 3);
    int** const pp_c_nums = &nums;
    print_ppint(pp_c_nums, 3);
    int* const * p_c_p_nums = &nums;
    print_p_c_pint(p_c_p_nums, 3);
    // *p_c_p_nums = nums_2;  //错误，不能修改*p_c_p_nums指向的值
    *pp_c_nums = nums_2; //正确，可以修改*pp_c_nums
    print_ppint(pp_c_nums, 3);
    // pp_c_nums = pp_c_nums; //错误，不能修改pp_c_nums的地址
    pp_nums = &nums_2;  //正确，可以修改pp_nums
    print_ppint(pp_nums, 3);
    // const int** c_pp_nums = &nums;  //错误，不能将int**赋给const int**

    return -1;
}