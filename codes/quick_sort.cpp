#include<iostream>
#include<vector>
#include<stack>
using namespace std;


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


int main(){
    vector<int> nums1 = {1,1,4,5,1,4,1,9,8,1,0};
    vector<int> nums2 = {1,1,4,5,1,4,1,9,8,1,0};
    vector<int> nums3 = {1,1,4,5,1,4,1,9,8,1,0};
    vector<int> nums4 = {1,1,4,5,1,4,1,9,8,1,0};
    vector<int> nums5 = {1,1,4,5,1,4,1,9,8,1,0};

    printf("原始数据: ");
    for (int i = 0; i <nums1.size(); i++)
    {
        printf("%d ", nums1[i]);
    }
    cout<<endl;

    my_sort_unrecursion(nums1);
    my_sort_recursion(nums2);
    my_bubblesort(nums3);
    my_selectsort(nums4);
    my_insertsort(nums5);

    printf("使用非递归的快速排序: ");
    for (int i = 0; i <nums1.size(); i++)
    {
        printf("%d ", nums1[i]);
    }
    cout<<endl;

    printf("使用递归的快速排序: ");
    for (int i = 0; i <nums2.size(); i++)
    {
        printf("%d ", nums2[i]);
    }
    cout<<endl;

    printf("冒泡排序: ");
    for (int i = 0; i <nums3.size(); i++)
    {
        printf("%d ", nums3[i]);
    }
    cout<<endl;

    printf("选择排序: ");
    for (int i = 0; i <nums4.size(); i++)
    {
        printf("%d ", nums4[i]);
    }
    cout<<endl;

    printf("插入排序: ");
    for (int i = 0; i <nums5.size(); i++)
    {
        printf("%d ", nums5[i]);
    }
    cout<<endl;

    return 0;
}