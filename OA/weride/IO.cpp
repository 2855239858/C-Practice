#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

int main() {
    string str1;

    cin>>str1;
    cout<<str1<<endl;

    string str2;
    str2.resize(15);
    scanf("%s", &str2[0]);
    cout<<str2<<endl;
    printf("%s\n", str2.c_str());
    printf("%s\n", str2.data());

    cout<<ceil(1 - 1)<<endl;
    cout<<ceil(1.2 - 1)<<endl;
    cout<<ceil(1.6 - 1)<<endl;
    cout<<ceil(0.2 - 1)<<endl;
    cout<<ceil(0.6 - 1)<<endl;

    return 0;
}