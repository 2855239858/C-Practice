#include <iostream>
#define INT1 int
typedef int INT2;
#define INT3 int*
typedef int* INT4;


int main() {
    {
        //space 1
        std::cout<<"Define int, typedef int:";
        INT1 a = 1, b = 2;
        INT2 c = 3, d = 4;
        std::cout<<a<<" "<<b<<" "<<c<<" "<<d<<""<<std::endl;
    }
    {
        //space 2
        std::cout<<"Define int*, typedef int*:";
        INT3 a, b = 2;
        INT4 c, d;
        a = new int(1);
        c = new int(3);
        d = new int(4);
        std::cout<<*a<<" "<<b<<" "<<*c<<" "<<*d<<""<<std::endl;
    }

    return -1;
}

///测试结果：
//（1）#define只是进行文本替换，因此对于space 2中b是一个int类型
//（2）typedef相当于类型别名，一次space 2中c和d都是int*类型