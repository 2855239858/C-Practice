#include<iostream>
#include<vector>
#include "algorithm.h"
using namespace std;

// ListNode* FindKthToTail1(ListNode* pListHead, unsigned int k) {
//     if(pListHead == nullptr) return nullptr;
    
//     int size = 0;
    
//     ListNode* tmp = pListHead;
//     while(tmp != nullptr){
//         size++;
//         tmp = tmp->next;
//     }
    
//     if(k > size) return nullptr;
    
//     tmp = pListHead;
//     for(size -= k; size > 0; size--){
//         tmp = tmp->next;
//     }
    
//     return tmp;
// }

// ListNode* FindKthToTail2(ListNode* pListHead, unsigned int k) {
//     if(pListHead == nullptr) return nullptr;
    
//     ListNode* slow = pListHead;
//     ListNode* fast = pListHead;
//     int k_th = k;
    
//     while(fast != nullptr && k_th-- > 0){
//         fast = fast->next;
//     }
//     if(k_th > 0) return nullptr;
        
//     while(fast != nullptr){
//         fast = fast->next;
//         slow = slow->next;
//     }
    
//     return slow;
// }

int main(void){
    vector<int> input_data = {1,2,3,4};
    ListNode* list = new ListNode(5);
    
    for(int i = input_data.size(); i > 0; i--){
        ListNode* tmp = new ListNode(input_data[i - 1]);
        tmp->next = list;
        list = tmp;
    }
    // reorderList2(list);
    // while(list != nullptr){
    //     cout<<list->val<<'-';
    //     list = list->next;
    // }
    cout<<FindKthToTail1(list, 1)->val<<endl<<FindKthToTail2(list, 1)->val;

    return 1;
}