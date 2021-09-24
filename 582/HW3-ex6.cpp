#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> ans;
int leftWall = 0;
int rightWall = 0;


int partition(std::vector<int>& nums, int l, int r) {
    int pivot = nums[r];
    int left = l;
    for(int i = l; i < r; ++i) {
        if(nums[i] <= pivot) {
            std::swap(nums[left++], nums[i]);
        }
    }
    std::swap(nums[left], nums[r]);

    return left;
}

void recursion(std::vector<int>& nums, int left, int right, int k) {
    if(left > right) return;

    if(left < leftWall) {
        left = leftWall;
    }
    if(right > rightWall) {
        right = rightWall;
    }

    if(rightWall - left < k - 1) return;
    if(right - leftWall < k - 1) return;

    int mid = partition(nums, left, right);

    if(mid - leftWall == k - 1) {
        ans.push_back(std::vector<int>(nums.begin() + leftWall, nums.begin() + mid + 1));
        leftWall = mid + 1;
        recursion(nums, leftWall, rightWall, k);
    } else if(rightWall - mid == k - 1) {
        ans.push_back(std::vector<int>(nums.begin() + mid, nums.begin() + rightWall + 1));
        rightWall = mid - 1;
        recursion(nums, leftWall, rightWall, k);
    } else {
        recursion(nums, left, mid - 1, k);
        recursion(nums, mid + 1, right, k);
    }
}

void splitArray(std::vector<int>& nums, int k) {
    rightWall = nums.size() - 1;
    recursion(nums, 0, nums.size() - 1, k);
}


struct TreeNode
{
    int value;
    TreeNode *leftNode;
    TreeNode *rightNode;

    TreeNode(int val): value(val), leftNode(nullptr), rightNode(nullptr) {}
    TreeNode(int val, TreeNode* left, TreeNode* right): value(val), leftNode(left), rightNode(right) {}
};

TreeNode* createBST(std::vector<int> nums) {
    return 
}

TreeNode* recursion(std::vector<int>& nums, int idxL, int idxR) {
    if(idxL > idxR) return nullptr;

    // get the index of the middle number
    int midIdx = idxL + (idxR - idxL) / 2;

    TreeNode *newNode = new TreeNode(nums[midIdx]);
    newNode->leftNode = recursion(nums, idxL, midIdx - 1);
    newNode->rightNode = recursion(nums, midIdx + 1, )

}



int main() {
    std::vector<int> nums = {4, 6, 7, 3, 2, 6, 7, 7, 3, 4, 5, 10};
    int k = 3;
    splitArray(nums, nums.size() / k);

    std::sort(ans.begin(), ans.end(), [](std::vector<int>& a, std::vector<int>& b) {
        return a.back() < b.back();
    });

    for(int i = 0; i < ans.size(); ++i) {
        for(int j = 0; j < ans[i].size(); ++j) {
            std::cout<<" "<<ans[i][j];
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

    return 1;
}