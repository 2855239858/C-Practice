#include <iostream>

using namespace std;

int main() {
    // 在自由存储区创建的数组对象是没有名字的，只能通过地址间接地访问堆中的对象
    // c++中，使用new和delete在堆（自由存储区）上分配和释放动态数组

    // 动态数组初始化
    // 1：元素只能初始化为元素类型的默认值，而不能像数组变量一样，用初始化列表为数组元素提供不同的初值。
    // 2：对于内置数据类型元素的数组，必须使用()来显示指定执行初始化操作，否则程序不执行初始化操作
    int *pia = new int[10]; // 元素没有初始值
    int *pia2 = new int[10] (); // 每个元素初始值为0

    // 3：类类型元素的数组，则无论是否使用()，都会自动调用其默认构造函数来初始化；
    string *psa = new string[10]; // 每个元素调用默认构造函数
    string *psa2 = new string[10] (); // 每个元素调用默认构造函数

    // 动态释放数组
    delete [] pia;

    // 一维数组初始化
    // 1:
    int value1[100]; // value[i]的值不定，没有初始化
    // 2:
    int value2[100] = {1, 2}; // value[0]和value[1]的值分别初始化为1和2，而没有定义的value[i>1]则初始化值为0
    // 3: 指针方法
    int *value3 = new int[100]; // 未初始化
    delete []value3; // 一定记得删除数组空间


    // 二维数组初始化
    // 1: 标准方法1
    int value4[9][9]; // value[i][j]的值不定，没有初始化
    // 2: 标准方法2
    int value5[9][9] = {{1, 1}, {2}}; // value[0][0,1]和value[1][0]的值初始化，其他初始化为0
    // 3: 指针方法1
    int (*value6)[9] = new int[10][9];
    delete []value6; // 低纬必须为常量。未初始化。
    // 4: 指针方法2
    int **value7 = new int* [9];
    for (int i = 0; i < 10; ++i) value7[i] = new int[9];
    for (int i = 0; i < 10; ++i) delete []value7[i]; 
    delete []value7; // 多次析构，存储麻烦，未初始化
    // 5: 指针方法3
    int *value8 = (int*) new int[3][4]; 
    delete []value8;

    // 6: 多维数组初始化
    int m = 10;
    int *value8 = (int*) new int[m][3][4]; // 只有一维可以是变量，其他几维必须是常量，否则报错
    delete []value8;
}

// 数组作为参数进行传递
// 1: 一维数组参数传递
void Func1(int* value) {}
// or
void Func2(int value[]) {}

// 2: 二维数组传递
// 定义为 int **value 形式的
void Func3(int** value) {}
// or 定义为 int (*value)[n] = new int[m][n] 形式的
void Func4(int (*value)[9]) {}
