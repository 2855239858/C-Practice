#include <iostream>
#include <vector>
#include <algorithm>

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

void findKRecursion(std::vector<int>& nums, int left, int right, int& leftW, int& rightW) {
    if(left > leftW && right < rightW) {
        return;
    }
    if(right < leftW || left > rightW) {
        return;
    }

    int mid = partition(nums, left, right);
    if(leftW == rightW) {
        if(mid == leftW) {
            leftW = -1;
            rightW = -1;
        } else {
            if(mid > leftW) {
                findKRecursion(nums, left, mid - 1, leftW, rightW);
            } else {
                findKRecursion(nums, mid + 1, right, leftW, rightW);
            }
        }
    } else {
        if(mid == leftW) {
            leftW = rightW;
        } else if(mid == rightW) {
            rightW = leftW;
        } else {
            findKRecursion(nums, left, mid - 1, leftW, rightW);
            findKRecursion(nums, mid + 1, right, leftW, rightW);
        }
    }
}

std::vector<int> findKClosestToMedium(std::vector<int>& nums, int k) {
    int n = nums.size();
    int leftW, rightW;
    if(n % 2 == 0) {
        leftW = n / 2 - k / 2;
        rightW = n / 2 + (k / 2 - 1);
    } else {
        leftW = n / 2 - k / 2;
        rightW = n / 2 + k / 2;
    }

    int left = leftW, right = rightW;
    findKRecursion(nums, 0, n - 1, leftW, rightW);

    return std::vector<int>(nums.begin() + left, nums.begin() + right + 1);
}

std::vector<std::vector<int>> ans;
int leftWall = 0;
int rightWall = 0;

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


int main() {

    // problem 6
    // std::vector<int> nums = {4, 6, 7, 3, 2, 6, 7, 7, 3, 4, 5, 10};
    // int k = 3;
    // splitArray(nums, nums.size() / k);

    // std::sort(ans.begin(), ans.end(), [](std::vector<int>& a, std::vector<int>& b) {
    //     return a.back() < b.back();
    // });

    // for(int i = 0; i < ans.size(); ++i) {
    //     for(int j = 0; j < ans[i].size(); ++j) {
    //         std::cout<<" "<<ans[i][j];
    //     }
    //     std::cout<<std::endl;
    // }
    // std::cout<<std::endl;


    // problem 5
    std::vector<int> nums1 = {2, 5, 6, 1, 3, 4};
    int k1 = 4;
    std::vector<int> ans1 = findKClosestToMedium(nums1, k1);

    std::vector<int> nums2 = {2, 7, 5, 6, 1, 3,4};
    int k2 = 5;
    std::vector<int> ans2 = findKClosestToMedium(nums2, k2);

    for(int i = 0; i < ans1.size(); ++i) {
        std::cout<<" "<<ans1[i];
    }
    std::cout<<std::endl;

    for(int i = 0; i < ans2.size(); ++i) {
        std::cout<<" "<<ans2[i];
    }
    std::cout<<std::endl;

    return 1;
}