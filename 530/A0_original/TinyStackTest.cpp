#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include <string>

#include "TinyStack.h"

using namespace std;


int main() {

    // test int
    Stack<int> s1;
    for (int i = 0; i < 10; ++i) {
        s1.push(i);
    }
    for (int i = 0; i < 10; ++i) {
        cout<<s1.pop()<<"  ";
    }
    cout<<endl;

    // test string
    Stack<string> s2;
    for (int i = 0; i < 10; ++i) {
        s2.push(string(i, 'a'));
    }
    for (int i = 0; i < 10; ++i) {
        cout<<s2.pop()<<"  ";
    }
    cout<<endl;

    // test float
    Stack<float> s3;
    for (int i = 0; i < 10; ++i) {
        s3.push(i);
    }
    for (int i = 0; i < 10; ++i) {
        cout<<s3.pop()<<"  ";
    }
    cout<<endl;

    // test char
    Stack<char> s4;
    for (int i = 0; i < 10; ++i) {
        s4.push('a' + i);
    }
    for (int i = 0; i < 10; ++i) {
        cout<<s4.pop()<<"  ";
    }
    cout<<endl;

    _CrtDumpMemoryLeaks();

    // getchar();
}
