#include<iostream>
#include<vector>
#include<unordered_map>
#include "data_struct.h"
using namespace std;

vector<int> delete_num(vector<int> A, vector<int> B){
    unordered_map<int, int> num_frequence;
    
    for(int i = 0; i < B.size(); i++){
        num_frequence[B[i]]++;
    }

    // int size = A.size();
    int k = 0;
    for(int i = 0; i < A.size(); i++){
        if(!num_frequence.count(A[i])){
            swap(A[i], A[k++]);
        }
    }

    return vector<int>(A.begin(), A.begin() + k);
}

int dfs(vector<vector<int>>& map, vector<int>& ans, int& size, int x, int y, int& rows, int& cols){
    if(x < 0||x >= rows||y < 0||y >= cols) return -1;
    if(map[x][y] != 0) return -1;
    else if(map[x][y] == 0){
        map[x][y] = -1;
        size++;
    }

    int up = dfs(map, ans, size, x - 1, y, rows, cols);
    int down = dfs(map, ans, size, x + 1, y, rows, cols);
    int left = dfs(map, ans, size, x, y - 1, rows, cols);
    int right = dfs(map, ans, size, x, y + 1, rows, cols);
    int up_left = dfs(map, ans, size, x - 1, y - 1, rows, cols);
    int up_right = dfs(map, ans, size, x - 1, y + 1, rows, cols);
    int down_left = dfs(map, ans, size, x + 1, y - 1, rows, cols);
    int down_right = dfs(map, ans, size, x + 1, y + 1, rows, cols);

    if(up == -1 && down == -1 && left == -1 && right == -1 && up_left == -1 && up_right == -1 && down_left == -1 && down_right == -1 && size != 0){
        ans.push_back(size);
        size = 0;
    }

    return 1;
}

int to_int(string s){
    int ans = 0;
    // ans = ans<<31;
    int j = 0;
    for(int i = 0; i < 4; i++){
        int tmp = 0;
        while(s[j] != '\0' && s[j] != '.'){
            tmp = tmp * 10 + (s[j] - '0');
            j++;
        }
        j++;
        tmp = tmp<<((3 - i) * 8);
        ans = ans | tmp;
    }

    return ans;
}

ListNode* merge_list(ListNode* list1, ListNode* list2){
    if(list1 ==nullptr || list2 == nullptr) return list1 == nullptr?list2:list1;

    ListNode* tmp_head = new ListNode(-1);
    ListNode* cur = tmp_head;
    
    while(list1 != nullptr && list2 != nullptr){
        if(list1->val > list2->val){
            cur->next = list2;
            list2 = list2->next;
        }else
        {
            cur->next = list1;
            list1 = list1->next;
        }
        cur = cur->next;
    }

    if(list1 != nullptr) cur->next = list1;
    if(list2 != nullptr) cur->next = list2;

    return tmp_head->next;

}
ListNode* cut_list(ListNode* root){
    if(root == nullptr) return root;

    ListNode* slow = root;
    ListNode* fast = root;

    while(fast != nullptr && fast->next != nullptr){
        fast = fast->next;
        if(fast->next != nullptr){
            fast = fast->next;
            slow = slow->next;
        }else
        {
            break;
        }
        
    }

    fast = slow->next;
    slow->next = nullptr;

    return fast;
}

ListNode* order_list(ListNode* root){
    if(root == nullptr || root->next == nullptr){
        return root;
    }
    ListNode* head1 = root;
    ListNode* head2 = cut_list(root);
    
    head1 = order_list(head1);
    head2 = order_list(head2);

    return merge_list(head1, head2);
}
int main(){
    //第一题：去除A数组中在B数组中的元素
    cout<<"第一题：";
    vector<int> A = {1,2,3,4,5,6};
    vector<int> B = {2,4,5};

    vector<int> ans1 = delete_num(A, B);
    for(auto a:ans1){
        cout<<a<<"  ";
    }
    cout<<endl;

    //第二题：找到所有水塘（元素为0，且上下左右和斜边相通的为同一水塘），并且记录它们的大小
    cout<<"第二题：";
    vector<vector<int>> map = {{0,0,1,0},
                                {0,1,1,1},
                                {1,1,0,0}};
    int rows = map.size(), cols = map[0].size();
    vector<int> ans2;
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            int size = 0;
            if(map[i][j] == 0) dfs(map, ans2, size, i, j, rows, cols);
        }
    }

    for(auto a:ans2){
        cout<<a<<"  ";
    }
    cout<<endl;

    //第三题：将一个192.168.0.1类似的网络地址转换成一个整数(一个区域的数字，例子中的192，不能大于等于128，不然转换后为负数)
    string net_add = "127.168.0.1";
    int ans3 = to_int(net_add);
    cout<<"第三题："<<ans3<<endl;

    //第四题：对链表进行排序,使用归并排序，时间复杂度O（nlogn），空间复杂度O（1）
    vector<int> nums = {1,5,2,3,7,4,5,6};
    ListNode* head = new ListNode(nums[0]);
    ListNode* cur = head;
    for(int i = 1; i < nums.size(); i++){
        ListNode* new_node = new ListNode(nums[i]);
        cur->next = new_node;
        cur = new_node;
    }
    head = order_list(head);
    cout<<"第四题：";
    while (head != nullptr)
    {
        cout<<head->val<<"  ";
        head = head->next;
    }
    cout<<endl;

    return -1;
}