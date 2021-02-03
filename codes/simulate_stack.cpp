#include<iostream>
#include<vector>
using namespace std;

class Solution{
public:
    virtual void push(int) = 0;
    virtual void pop() = 0;
    virtual int top() = 0;
    virtual int min() = 0;
 };


class Solution1:Solution {
private:
    int nums[100];
    int size;
public:
    Solution1(){
        this->size = 0;
    }
    void push(int value) {
        this->nums[size] = value;
        this->size++;
    }
    void pop() {
        if(this->size) this->size--;
    }
    int top() {
        if(this->size) return this->nums[this->size - 1];
        else return -1;
    }
    int min() {
        if(this->size){
            int min_num = this->nums[0];
            
            for(int i = 0; i < this->size; i++){
                if(min_num > this->nums[i]){
                    min_num = this->nums[i];
                }
            }
            
            return min_num;
        }
        
        return -1;
    }
};

#include<stack>

class Solution2:Solution {
private:
    stack<int> stack1, stack2;
public:
    void push(int value) {
        if(stack2.empty() || stack2.top() >= value){
            stack1.push(value);
            stack2.push(value);
        }else{
            stack1.push(value);
        }
    }
    void pop() {
        if(stack1.top() == stack2.top()){
            stack1.pop();
            stack2.pop();
        }else{
            stack1.pop();
        }
    }
    int top() {
        return stack1.top();
    }
    int min() {
        return stack2.top();
    }
};

int main(void){
    Solution1* exam1 = new Solution1();
    exam1->push(5);
    exam1->push(2);
    exam1->push(6);
    exam1->push(2);
    cout<<"Solution1: top() test: "<<exam1->top()<<endl;
    exam1->pop();
    cout<<"Solution1: top() test: "<<exam1->top()<<endl;
    cout<<"Solution1: min() test: "<<exam1->min()<<endl;

    Solution2* exam2 = new Solution2();
    exam2->push(5);
    exam2->push(2);
    exam2->push(6);
    exam2->push(2);
    cout<<"Solution2: top() test: "<<exam2->top()<<endl;
    exam2->pop();
    cout<<"Solution2: top() test: "<<exam2->top()<<endl;
    cout<<"Solution2: min() test: "<<exam2->min()<<endl;

    return 1;
}