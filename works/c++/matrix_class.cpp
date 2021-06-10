#include <iostream>
#include <vector>
// #include <cstdint>

struct Filter {
    inline Filter() : filterType(0) {} 

    int filterType;
    int cameraMask[128 / 8];
    int timeRange[2];
};

void PrintFilterType(const Filter filters[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout<<filters[i].filterType<<" ";
        // filters[i].filterType = 0;
    }
    std::cout<<std::endl;
}

int main() {
    Filter* filters = new Filter[10];
    for (int i = 0; i < 10; i++) {
        filters[i].filterType = i;
    }
    PrintFilterType(filters + 5, 10);

    std::vector<Filter> filters_2(10);
    for (int i = 0; i < 10; i++) {
        filters_2[i].filterType = i + 10;
    }
    std::vector<Filter>::const_iterator ite = filters_2.begin();
    PrintFilterType(&filters_2[5], 10);
    PrintFilterType(&*(ite + 5), 10);
    
    return -1;
}