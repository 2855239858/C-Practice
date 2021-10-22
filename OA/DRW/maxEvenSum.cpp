#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <algorithm>

using namespace std;
 
int maxEvenSum(vector<int>& nums, int k) {
    int n = nums.size();
    if (k > n) return -1;
    if (k == n) return accumulate(nums.begin(), nums.end(), 0);
    
    int ret = 0;
    priority_queue<int, vector<int>, less<int>> evens;
    priority_queue<int, vector<int>, less<int>> odds;

    for (int i = 0; i < n; ++i) {
        if (nums[i] % 2 == 1) {
            odds.push(nums[i]);
        } else {
            evens.push(nums[i]);
        }
    }

    if (evens.size() / 2 * 2 + odds.size() / 2 * 2 < k) {
        return -1;
    }

    if (k % 2 == 1) {
        if (evens.size() > 0) {
            ret += evens.top();
            evens.pop();
            k -= 1;
        } else {
            return -1;
        }
    }

    while (k > 0) {
        int even1 = 0, even2 = 0;
        int odd1 = 0, odd2 = 0;
        if (evens.size() >= 2) {
            even1 = evens.top();
            evens.pop();
            even2 = evens.top();
            evens.pop();
        }
        if (odds.size() >= 2) {
            odd1 = odds.top();
            odds.pop();
            odd2 = odds.top();
            odds.pop();
        }
        int sumEven = even1 + even2;
        int sumOdd = odd1 + odd2;
        if (sumEven > sumOdd) {
            ret += sumEven;
            odds.push(odd2);
            odds.push(odd1);
        } else {
            ret += sumOdd;
            evens.push(even2);
            evens.push(even1);
        }
        k -= 2;
    }

    return ret;
}

int main() {
    vector<int> nums1 = {4,9,8,2,6}; int k1 = 3;
    vector<int> nums2 = {5,6,3,4,2}; int k2 = 5;
    vector<int> nums3 = {7,7,7,7,7}; int k3 = 1;
    vector<int> nums4 = {10000}; int k4 = 2;
    vector<int> nums5 = {2,3,3,5,5}; int k5 = 3;

    cout<<"Ans 1: "<<maxEvenSum(nums1, k1)<<endl;
    cout<<"Ans 2: "<<maxEvenSum(nums2, k2)<<endl;
    cout<<"Ans 3: "<<maxEvenSum(nums3, k3)<<endl;
    cout<<"Ans 4: "<<maxEvenSum(nums4, k4)<<endl;
    cout<<"Ans 5: "<<maxEvenSum(nums5, k5)<<endl;

    return 0;
}