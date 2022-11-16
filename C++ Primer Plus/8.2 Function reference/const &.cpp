// Online C++ compiler to run C++ program online
#include <iostream>

struct pos {
  int x;
  int y;
  pos(int _x, int _y): x(_x), y(_y) {}
  void print() const { std::cout<<x<<"-"<<y<<std::endl; }
  void changeX(int _x) {
      x = _x;
  }
  void changeY(int _y) {
      y = _y;
  }
  void do_nothing() { }
  void do_nothing_with_const() const { }
};

void modifyPos(const pos& p) {
    // pos newPos(1, 2);
    // p = newPos;  // invalid
    
    // p.x = 2;    // invalid
    // p.y = 3;    // invalid
    
    // p.changeX(2);   // invalid
    // p.changeY(3);   // invalid
    
    // p.print();  // invalid
    
    // p.do_nothing();  // invalid
    
    p.do_nothing_with_const();  // valid
    
    p.print();
}

void modifyBasicValue(const int& a) {
    std::cout<<"Basic value: "<<a<<std::endl;
}

int main() {
    // Write C++ code here

    pos p(1, 1);
    p.print();

    modifyPos(p);

    modifyBasicValue(1);  // valid: value type correct but right-hand value
    float a = 1.2;
    modifyBasicValue(a);    // valid: value type wrong, and left-hand value
    modifyBasicValue(2.2);      // valid: value type wrong, and right-hand value
    
    return 0;
}