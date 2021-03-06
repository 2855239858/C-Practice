#include<iostream>
#include<vector>
using namespace std;

int main(){

    cout<<"init vector"<<endl;
    vector<int> test;
    cout<<"size:"<<test.size()<<"---"<<"capacity:"<<test.capacity()<<endl;

    test.push_back(1);
    cout<<"push_back 1"<<endl;
    cout<<"size:"<<test.size()<<"---"<<"capacity:"<<test.capacity()<<endl;

    test.push_back(2);
    cout<<"push_back 2"<<endl;
    cout<<"size:"<<test.size()<<"---"<<"capacity:"<<test.capacity()<<endl;
    
    test.reserve(10);
    cout<<"vector reserve 10"<<endl;
    cout<<"size:"<<test.size()<<"---"<<"capacity:"<<test.capacity()<<endl;

    test.push_back(3);
    cout<<"push_back 3"<<endl;
    cout<<"size:"<<test.size()<<"---"<<"capacity:"<<test.capacity()<<endl;

    test.resize(5);
    cout<<"vector resize 5"<<endl;
    cout<<"size:"<<test.size()<<"---"<<"capacity:"<<test.capacity()<<endl;

    test.push_back(4);
    cout<<"push_back 4"<<endl;
    cout<<"size:"<<test.size()<<"---"<<"capacity:"<<test.capacity()<<endl;

    test.reserve(5);
    cout<<"vector reserve 5"<<endl;
    cout<<"size:"<<test.size()<<"---"<<"capacity:"<<test.capacity()<<endl;

    test.resize(10);
    cout<<"vector resize 10"<<endl;
    cout<<"size:"<<test.size()<<"---"<<"capacity:"<<test.capacity()<<endl;

    test.push_back(5);
    cout<<"push_back 5"<<endl;
    cout<<"size:"<<test.size()<<"---"<<"capacity:"<<test.capacity()<<endl;
    return - 1;
}