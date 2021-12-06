#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> nums1 = {1, 2, 3};
    vector<int> nums2 = {1, 2, 3};
    vector<int> nums3 = {1, 2, 4};

    cout<<(nums1 == nums2)<<endl;
    cout<<(nums2 == nums3)<<endl;
    
    return 0;
}