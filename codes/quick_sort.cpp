#include<iostream>
#include<vector>
#include<stack>
using namespace std;


//��������ָ1������ָ����������α���
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

//��������ָ2������ָ��ֱ����м俿�룬ע�⣡���������һЩbug
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

//��������ָ3������ָ�����м俿�룬��������ָ���Ƿֱ��߶�Ȼ���滻����2��ͬ��
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

//��������ʹ�õݹ鷽���汾
void my_sort_recursion(vector<int> & nums){
    int left = 0;
    int right = nums.size() - 1;
    sort_recursion(nums, left, right);
}

//��������ʹ�÷ǵݹ鷽���汾��ͨ��ʵ��һ��ջ��ģ��ݹ�
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

//ð������
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

//ѡ������
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

//��������
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

    printf("ԭʼ����: ");
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

    printf("ʹ�÷ǵݹ�Ŀ�������: ");
    for (int i = 0; i <nums1.size(); i++)
    {
        printf("%d ", nums1[i]);
    }
    cout<<endl;

    printf("ʹ�õݹ�Ŀ�������: ");
    for (int i = 0; i <nums2.size(); i++)
    {
        printf("%d ", nums2[i]);
    }
    cout<<endl;

    printf("ð������: ");
    for (int i = 0; i <nums3.size(); i++)
    {
        printf("%d ", nums3[i]);
    }
    cout<<endl;

    printf("ѡ������: ");
    for (int i = 0; i <nums4.size(); i++)
    {
        printf("%d ", nums4[i]);
    }
    cout<<endl;

    printf("��������: ");
    for (int i = 0; i <nums5.size(); i++)
    {
        printf("%d ", nums5[i]);
    }
    cout<<endl;

    return 0;
}