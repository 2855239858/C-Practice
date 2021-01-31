#include<iostream>
#include<vector>
#include "data_struct.h"
#include<ctime>
using namespace std;

vector<int> unrecursion_printListFromTailToHead(ListNode* head) {
    if(head == nullptr) return {};
    
    vector<int> ans;
    while(head != nullptr){
        ans.push_back(head->val);
        head = head->next;
    }
    
    int left = 0;
    for(int right  = ans.size() - 1; left < right; left++, right--){
        swap(ans[left], ans[right]);
    }
    
    return ans;
}

//递归的写法
vector<int> recursion_printListFromTailToHead(ListNode* head) {
    vector<int> ans;
    
    if(head != nullptr){
        ans = recursion_printListFromTailToHead(head->next);
        ans.push_back(head->val);
    }
    
    return ans;
}

int main(){
    ListNode* list = new ListNode(0);
    ListNode* tmp = list;

    // cout<< "链表中的原始数据:" << endl << "0 ";
    for(int i = 1; i < 20000; i++){
        // cout<< i << " ";
        ListNode* newnode = new ListNode(i);
        tmp->next = newnode;
        tmp = tmp->next;
    }
    cout<< endl;

    clock_t startTime_recursion, endTime_recursion, startTime_unrecursion, endTime_unrecursion;
    vector<int> recursion_ans;
    vector<int> unrecursion_ans;

    startTime_recursion = clock();
    recursion_ans = recursion_printListFromTailToHead(list);
    endTime_recursion = clock();

    startTime_unrecursion = clock();
    unrecursion_ans = unrecursion_printListFromTailToHead(list);
    endTime_unrecursion = clock();

    cout<<"递归版本运行时间： " << (double)(endTime_recursion - startTime_recursion) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
    // for(int i = 0; i < 10000; i++){
        // cout<<recursion_ans[i]<<' ';
    // }
    // cout<<endl;

    cout<<"非递归版本运行时间： " << (double)(endTime_unrecursion - startTime_unrecursion) * 1000 / CLOCKS_PER_SEC << "ms" << endl;
    // for(int i = 0; i < 10000; i++){
        // cout<<unrecursion_ans[i]<<' ';
    // }
    // cout<<endl;
    
    cout<<"整个程序运行时间（创建链表+两种倒置方法）: " << (double)clock() * 1000 / CLOCKS_PER_SEC << "ms" << endl;

    return -1;
}