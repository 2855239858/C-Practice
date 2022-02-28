#include <iostream>

#include <memory>
#include <string>

using namespace std;

class test {
public:
    test() {

    }
};

typedef shared_ptr <test> testPtr;

int main() {
    test *t1 = new test();
    cout<<"original address: "<<t1<<endl;

    testPtr t2 = make_shared<test>();
    testPtr t3 = t2;

    cout<<"t2: "<<t2<<"-t2 original address: "<<t2.get()<<endl;
    cout<<"t3: "<<t3<<"-t3 original address: "<<t3.get()<<endl;

    getchar();
    return 0;
}