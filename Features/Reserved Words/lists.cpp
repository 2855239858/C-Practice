#include <iostream>
#include <limits.h> // LLONG_MAX, LLONG_MIN, INT_MAX, INT_MAX
#include <cfloat>   // DBL_MAX, DBL_MIN, FLT_MAX, FLT_MIN

#include <limits>   // numeric_limits<type>::max/min

using namespace std;
#define int_max numeric_limits<int>::max()
#define int1 123

int main() {
    cout<<"long long int max: "<<LLONG_MAX<<endl;
    cout<<"long long int min: "<<LLONG_MIN<<endl;
    // cout<<__DBL_MAX__<<endl;
    cout<<"double max: "<<DBL_MAX<<endl;
    cout<<"double min: "<<DBL_MIN<<endl;
    cout<<"long int max: "<<LONG_MAX<<endl;
    cout<<"long int min: "<<LONG_MIN<<endl;
    cout<<"int max: "<<INT_MAX<<endl;
    cout<<"int min: "<<INT_MIN<<endl;
    cout<<"float max: "<<FLT_MAX<<endl;
    cout<<"float min: "<<FLT_MIN<<endl;
    // and so on

    cout<<endl<<endl;
    // or we can use numeric_limits<type>::max/min
    cout<<"numeric_limits<long long>::max: "<<numeric_limits<long long>::max()<<endl;
    cout<<"numeric_limits<long long>::min: "<<numeric_limits<long long>::min()<<endl;  
    cout<<"numeric_limits<double>::max: "<<numeric_limits<double>::max()<<endl;
    cout<<"numeric_limits<double>::min: "<<numeric_limits<double>::min()<<endl;
    cout<<"numeric_limits<long>::max: "<<numeric_limits<long>::max()<<endl;
    cout<<"numeric_limits<long>::min: "<<numeric_limits<long>::min()<<endl;
    cout<<"numeric_limits<int>::max: "<<numeric_limits<int>::max()<<endl;
    cout<<"numeric_limits<int>::min: "<<numeric_limits<int>::min()<<endl;
    cout<<"numeric_limits<float>::max: "<<numeric_limits<float>::max()<<endl;
    cout<<"numeric_limits<float>::min: "<<numeric_limits<float>::min()<<endl;

    cout<<"define: "<<int_max<<endl;
    cout<<int1<<endl;

    getchar();
    return 1;
}
