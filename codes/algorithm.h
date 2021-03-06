#include<iostream>
#include<vector>
#include<stack>
#include "data_struct.h"
using namespace std;

ListNode* FindKthToTail1(ListNode* pListHead, unsigned int k) {
    if(pListHead == nullptr) return nullptr;
    
    int size = 0;
    
    ListNode* tmp = pListHead;
    while(tmp != nullptr){
        size++;
        tmp = tmp->next;
    }
    
    if(k > size) return nullptr;
    
    tmp = pListHead;
    for(size -= k; size > 0; size--){
        tmp = tmp->next;
    }
    
    return tmp;
}

ListNode* FindKthToTail2(ListNode* pListHead, unsigned int k) {
    if(pListHead == nullptr) return nullptr;
    
    ListNode* slow = pListHead;
    ListNode* fast = pListHead;
    int k_th = k;
    
    while(fast != nullptr && k_th-- > 0){
        fast = fast->next;
    }
    if(k_th > 0) return nullptr;
        
    while(fast != nullptr){
        fast = fast->next;
        slow = slow->next;
    }
    
    return slow;
}

//快速排序分割法1：两个指针从左到右依次遍历
int partition1(vector<int>& nums, int left, int right){
    int pivot = nums[right];
    int i = left;
    for(int j = left; j < right; j++){
        if(nums[j] <= pivot){
            swap(nums[i++], nums[j]);
        }
    }
    swap(nums[i], nums[right]);
    
    return i;
}

//快速排序分割法2：左右指针分别向中间靠齐，注意！！！这个有一些bug
int partition2(vector<int> & nums, int left , int right){
    int pivot = nums[right];
    int end = right;
    right--;

    while (left < right)
    {
        while (left < right && nums[left] < pivot)
        {
            left++;
        }
        while (left < right && nums[right] > pivot)
        {
            right--;
        }
        
        if(left < right) swap(nums[left], nums[right]);
        
    }
    // if(nums[left] > nums[end]) swap(nums[left], nums[end]);
    swap(nums[left], nums[end]);


    return left;
}

//快速排序分割法3：左右指针向中间靠齐，但是左右指针是分别走动然后替换，和2不同。
int partition3(vector<int>& nums, int left, int right) {
    int pivot = nums[left];

    while (left < right)
    {
        while (left < right && nums[right] >= pivot)
        {
            right--;
        }
        nums[left] = nums[right];
        while (left < right && nums[left] <= pivot)
        {
            left++;
        }
        nums[right] = nums[left];
    }
    nums[left] = pivot;

    return left;
}

void sort_recursion(vector<int> & nums, int left, int right){
    if(left < right){
        int tmp = partition3(nums, left, right);
        sort_recursion(nums, left, tmp - 1);
        sort_recursion(nums, tmp + 1, right);
    }
}

//快速排序：使用递归方法版本
void my_sort_recursion(vector<int> & nums){
    int left = 0;
    int right = nums.size() - 1;
    sort_recursion(nums, left, right);
}

//快速排序：使用非递归方法版本，通过实现一个栈来模拟递归
void my_sort_unrecursion(vector<int>& nums){
    stack<int> edges;
    edges.push(0);
    edges.push(nums.size() - 1);

    while (!edges.empty())
    {
        int high = edges.top();
        edges.pop();
        int low = edges.top();
        edges.pop();
        int mid = partition3(nums, low, high);

        if (low < mid - 1)
        {
            edges.push(low);
            edges.push(mid - 1);
        }
        if (mid + 1 < high)
        {
            edges.push(mid + 1);
            edges.push(high);
        }
    }
    
}

//冒泡排序
void my_bubblesort(vector<int>& nums){
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < i; j++)
        {
            int tmp;
            if (nums[j] > nums[j + 1])
            {
                tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
    }
}

//选择排序
void my_selectsort(vector<int>& nums){
    int min_index;

    for(int i = 0; i < nums.size(); i++){
        min_index = i;
        for(int j = (i + 1); j < nums.size(); j++){
            if(nums[j] < nums[min_index]){
                min_index = j;
            }
        }
        if(min_index != i){
            int tmp = nums[i];
            nums[i] = nums[min_index];
            nums[min_index] = tmp;
        }
    }
}

//插入排序
void my_insertsort(vector<int>& nums){
    for(int i = 1; i < nums.size(); i++){
        for(int j = i - 1; j >= 0 && nums[j] > nums[j + 1]; j--){
            int tmp = nums[j];
            nums[j] = nums[j + 1];
            nums[j + 1] = tmp;
        }
    }
}

int arrange(int single, int doub){
    long long up = 1, down = 1;
    
    for(int i = single + doub; i > single; i--){
        up *= i;
    }
    for(int i = doub; i > 0; i--){
        down *= i;
    }
    
    return up / down;
}

int rectCover1(int number) {
    if(number == 0) return 0;
    
    int doub = number / 2;
    int ans = 1;
    
    for(int i = 1; i <= doub; i++){
        ans += arrange(number - i * 2, i);
    }
    
    return ans;
}

int rectCover2(int number) {
    if(number == 0 || number == 1) return number == 0? 0: 1;
    if(number == 2) return 2;
    
    int pre1 = 1, pre2 = 2, ans;
    
    for(int i = 3; i <= number; i++)
    {
        ans = pre1 + pre2;
        pre1 = pre2;
        pre2 = ans;
    }
    
    return ans;
}

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

ListNode* reverse_node(ListNode* node){
    if(node == nullptr) return node;
    
    ListNode* new_node = new ListNode(-1);
    new_node->next = node;
    while(node->next != nullptr){
        ListNode* tmp = node->next;
        node->next = tmp->next;
        tmp->next = new_node->next;
        new_node->next = tmp;
    }
    
    return new_node->next;
}

void reorderList1(ListNode *head) {
    if(!head) return;
    ListNode* slow = head;
    ListNode* fast = head;
    
    while(fast != nullptr && fast->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode* mid = slow->next;
    slow->next = nullptr;
    mid = reverse_node(mid);
    fast = head;
    while(mid != nullptr && fast != nullptr){
        ListNode* tmp = mid;
        mid = mid->next;
        tmp->next = fast->next;
        fast->next = tmp;
        fast = tmp->next;
    }
    while(head != nullptr){
        cout<<head->val<<'-';
        head = head->next;
    }
}

void reorderList2(ListNode *head) {
    if(!head) return;
    vector<ListNode*> list_nodes;
    ListNode* tmp = head;
    while(tmp != nullptr){
        list_nodes.push_back(tmp);
        tmp = tmp->next;
    }
    int i = 0, j = list_nodes.size() - 1;
    for(; i < j; i++, j--){
        list_nodes[j]->next = list_nodes[i]->next;
        list_nodes[i]->next = list_nodes[j];
    }

    list_nodes[i]->next = nullptr;
    
    while(head != nullptr){
        cout<<head->val<<'-';
        head = head->next;
    }
}

double getCubeRoot(double input){
    double ans = 1.0;

    do{
        ans = ans - (ans * ans * ans - input)/(3 * ans * ans);
    }while(ans * ans * ans - input > 0.01 || ans * ans * ans - input < -0.01);

    return ans;
}