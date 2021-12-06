#include <iostream>

using namespace std;


// n字节的对齐方式，VC对结构的存储的特殊处理确实提高CPU存储
// 变量的速度，但是有时候也带来了一些麻烦。我们可以屏蔽变量
// 的默认对其方式，自己可以设定变量的对齐方式。VC中提供了
// #pragma pack(n)来设定变量以n字节对齐方式。

// (1) 如果n大于等于该变量所占用的字节数，那么偏移量必须满足
// 默认的对齐方式。

// (2) 如果n小于该变量的类型所占用的字节数，那么偏移量为n的倍数
// 不用满足默认的对齐方式。

// (3) 结构的总大小也有约束，分两种情况：如果n大于所有成员变量
// 类型所占用的字节数，那么结构的总大小必须为占用空间最大的变量
// 所占用的空间数的倍数；否则必须为n的倍数。

// 默认对齐方式，以最大变量4为基准
struct node        // 12
{
    char f;         // 4
    int e;          // 4
    short int a;    // a + b = 4
    char b;
};

node n;

// 以1对齐
#pragma pack(push)  // 保存对齐方式
#pragma pack(1)

struct node1        // 8
{
    char f;         // 1
    int e;          // 4
    short int a;    // 2
    char b;         // 1
};

node1 n1;

#pragma pack(pop)   // 恢复对齐方式

// 以2对齐
#pragma pack(push)
#pragma pack(2)

struct node2        // 10
{
    char f;         // 2
    int e;          // 4
    short int a;    // 2
    char b;         // 2
};

node2 n2;

#pragma pack(pop)

// 以4对齐
#pragma pack(push)
#pragma pack(4)

struct node3        // 12
{
    char f;         // 4
    int e;          // 4
    short int a;    // a + b = 4
    char b;
};

node3 n3;

#pragma pack(pop)

// 以8对齐
#pragma pack(push)
#pragma pack(8)

struct node4        // 12
{
    char f;         // 4
    int e;          // 4
    short int a;    // a + b = 4
    char b;
};

node4 n4;

#pragma pack(pop)

int main() {
    cout<<sizeof(n)<<endl;
    cout<<sizeof(n1)<<endl;
    cout<<sizeof(n2)<<endl;
    cout<<sizeof(n3)<<endl;
    cout<<sizeof(n4)<<endl;


    node1 N1;
    node2 N2;
    node3 N3;
    cout<<sizeof(N1)<<endl;
    cout<<sizeof(N2)<<endl;
    cout<<sizeof(N3)<<endl;

    return 0;
}