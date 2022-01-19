#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
using namespace std;
int K[90];
int main()
{
    int *k = (int*)malloc(100);
    //free(k);
    const int m = 10;
    int M[m];
    cout << &m << endl;
    int s=m;
    cout << s << endl;
    s = 100;
    cout << &s << endl;
    _CrtDumpMemoryLeaks();
    system("pause");
    return 0;
}