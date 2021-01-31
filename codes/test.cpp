#include <iostream>
using namespace std;

template<typename T, typename U> T my_max(T a,U b){
    return a > b ? a : b;
}

template<class T> class my_Max{
private:
    T a;
    T b;
public:
    my_Max(T a, T b);

    T which_bigger();
};

template<typename T> my_Max<T>::my_Max(T a, T b){
    this->a = a;
    this->b = b;
}

template<typename T> T my_Max<T>::which_bigger(){
    return this->a > this->b ? this->a : this->b;
}

int main()
{
    char a = 'b', b = 'w';
    my_Max<char> ans(a,b);
    printf("template function : %c \n", my_max(a,b));
    printf("template class : %c \n", ans.which_bigger());

    return 0;
}