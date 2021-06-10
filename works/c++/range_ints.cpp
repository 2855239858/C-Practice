#include <stdint.h>
#include <iostream>
#include <string.h>

const int BitsPerMaskField = 8;

struct IDFilter {
    IDFilter() {
        for(int i = 0; i < (128 / BitsPerMaskField); i++) cameraMask[i] = __UINT8_MAX__;
        timeRange[0] = 0;
        timeRange[1] = __UINT32_MAX__;
    }
    uint8_t cameraMask[128 / BitsPerMaskField] = {__UINT8_MAX__};
    uint32_t timeRange[2] = {0};
};

namespace faiss {
    struct IDFilter {
    uint8_t camera_Mask[128 / BitsPerMaskField];
    uint32_t time_Range[2];
    };
}

template<typename filter>
void printFilters(filter* filters, int size) {
    // std::cout<<"printFilter---szieof: "<<sizeof(filters)<<std::endl;
    for(int i = 0; i < size; i++) {
        std::cout<<"printFilters---Filter "<<i<<"---";

        for(int j = 0; j < (128 / BitsPerMaskField); j++) std::cout<<(int)filters[i].cameraMask[j]<<" ";
        std::cout<<filters[i].timeRange[0]<<"~"<<filters[i].timeRange[1]<<std::endl;
    }
}

template<typename filter>
void print_Filters(filter* filters, int size) {
    // std::cout<<"print_Filter---szieof: "<<sizeof(filters)<<std::endl;
    for(int i = 0; i < size; i++) {
        std::cout<<"print_Filters---Filter "<<i<<"---";

        for(int j = 0; j < (128 / BitsPerMaskField); j++) std::cout<<(int)filters[i].camera_Mask[j]<<" ";
        std::cout<<filters[i].time_Range[0]<<"~"<<filters[i].time_Range[1]<<std::endl;
    }
}

int main() {
    int size = 3;
    IDFilter *filters = new IDFilter[size];
    printFilters<IDFilter>(filters, size);
    IDFilter filters_2[size];

    faiss::IDFilter* faiss_filters = (faiss::IDFilter*)filters;
    print_Filters<faiss::IDFilter>(faiss_filters, size);

    faiss::IDFilter* faiss_filters_2 = new faiss::IDFilter[size];
    print_Filters<faiss::IDFilter>(faiss_filters_2, size);
    // std::copy(&faiss_filters[0], &faiss_filters[size], faiss_filters_2); //正确，faiss_filters与faiss_filters_2拥有相同类型，可以直接进行copy
    // std::copy(&filters[0], &filters[size], (IDFilter*)faiss_filters_2);  //正确，将faiss_filters_2类型从faiss::IDFilter转换到IDFilter也是可以
    // std::copy((faiss::IDFilter*)&filters[0], (faiss::IDFilter*)&filters[size], faiss_filters_2);  //正确，将filters类型转换到faiss::IDFilter也是可以
    memcpy(faiss_filters_2, filters, sizeof(filters[0]) * size); 
    std::cout<<sizeof(*filters)<<" "<<sizeof(*filters)<<" "<<sizeof(filters)<<" "<<sizeof(filters_2)<<std::endl;
    printFilters<IDFilter>(filters_2, size);
    print_Filters<faiss::IDFilter>(faiss_filters_2, size);

    std::cout<<"Change Filters"<<std::endl;
    filters[0].cameraMask[0] = 0;
    printFilters<IDFilter>(filters, size);
    // delete [] filters; //删除filters后下一步print faiss_filters会出现不能设想的情况。
    // filters = NULL;
    // printFilters<IDFilter>(filters, size);
    // printFilters<faiss::IDFilter>(faiss_filters, size);
    print_Filters<faiss::IDFilter>(faiss_filters_2, size);

    std::cout<<"Wild Pointers Test"<<std::endl;
    // delete [] filters;
    // IDFilter* filters_2 = new IDFilter[size];
    // filters_2[0].cameraMask[0] = 1;
    // printFilters<IDFilter>(filters_2, size);
    // printFilters<IDFilter>(filters, size);
    // printFilters<faiss::IDFilter>(faiss_filters, size);


    return -1;
}

///测试结果：
//（1）当不同结果拥有相同数据结构的时候，可以使用指针类型强制转换来进行地址赋值：如filters和faiss_filters指向同一块地址。
//（2）使用copy函数的时候，拥有相同数据结构的不同结构也可以进行复制，但是需要将类型强制转换到同一类型。
//（3）copy函数是将地址中的内容复制一边，也就是深拷贝；与对指针类型进行强制转换后进行赋值不同（1）
//（4）当我们删除指针的时候，编译器释放掉指针指向的内存空间以后记得将指针置为nullptr/NULL，不然会出现野指针。（若多个指针指向同一块地址，所有指向这个地址的指针都应该置为nullptr/NULL）
//（5）memcpy也可以进行结构体的深拷贝，需要指名拷贝字节数，因此如果只有指针还不够，还需要知道数组的长度
//（6）在使用copy和memcpy拷贝有相同类型和大小的数据结构的结构体，其中的数据的名字可以不一样
