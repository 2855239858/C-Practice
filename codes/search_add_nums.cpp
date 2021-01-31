#include<iostream>
#include<vector>
using namespace std;

vector<vector<int>> ans;
vector<int> tmp;

void search_add_repeat_nums(vector<int> nums, int val, int index){
    for(int i = index; i < nums.size(); i++){
        if(val == nums[i]){
            tmp.push_back(nums[i]);
            ans.push_back(tmp);
            tmp.pop_back();
        }else if(val > nums[i]){
            tmp.push_back(nums[i]);
            search_add_repeat_nums(nums, val - nums[i], i);
            tmp.pop_back();
        }else
        {
            break;
        }
        
    }
}

void search_add_norepeat_nums(vector<int> nums, int val, int index){
    for(int i = index; i < nums.size(); i++){
        if(val == nums[i]){
            tmp.push_back(nums[i]);
            ans.push_back(tmp);
            tmp.pop_back();
        }else if(val > nums[i]){
            tmp.push_back(nums[i]);
            search_add_norepeat_nums(nums, val - nums[i], i + 1);
            tmp.pop_back();
        }else
        {
            break;
        }
        
    }
}

int main(){
    vector<int> A = {2,3,5,7};
    int x = 7;

    for(int z = 0; z < 2; z++){
        if(z == 0){
            cout<<"查找含有重复数字的组合:"<<endl;
            search_add_repeat_nums(A, x, 0);
        }else
        {
            cout<<"查找不含有重复数字的组合:"<<endl;
            search_add_norepeat_nums(A, x, 0);
        }

        for(int i = 0; i < ans.size(); i++){
            for(int j = 0; j < ans[i].size(); j++){
                printf("%d ", ans[i][j]);
            }
            cout<<endl;
        }
        ans.clear();
    }

    return 0;
}