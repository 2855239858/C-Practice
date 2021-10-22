#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <math.h>
#include <stack>
#include <algorithm>

struct TreeNode
{
    int value;
    TreeNode *leftNode;
    TreeNode *rightNode;

    TreeNode(int val): value(val), leftNode(nullptr), rightNode(nullptr) {}
    TreeNode(int val, TreeNode* left, TreeNode* right): value(val), leftNode(left), rightNode(right) {}
};

TreeNode* recursion(std::vector<int>& nums, int idxL, int idxR) {
    if(idxL > idxR) return nullptr;

    // get the index of the middle number
    int midIdx = idxL + (idxR - idxL) / 2;

    // create a new node as the middle number
    TreeNode *newNode = new TreeNode(nums[midIdx]);
    // put numbers less than middle number in the left child
    newNode->leftNode = recursion(nums, idxL, midIdx - 1);
    // put numbers greater than middle number in the right child
    newNode->rightNode = recursion(nums, midIdx + 1, idxR);

    return newNode;
}

TreeNode* createBST(std::vector<int> nums) {
    return recursion(nums, 0, nums.size() - 1);
}

TreeNode* createBSTwithoutRecursion(std::vector<int> nums) {
    int n = nums.size();
    if(n == 0) return nullptr;

    // idxS is used for storing left idx and right idx
    // of different partitions, keep left idx behind right idx
    std::stack<int> idxS;
    idxS.push(n - 1);
    idxS.push(0);

    // store nodes
    std::stack<TreeNode*> nodeS;
    TreeNode *root = new TreeNode(0);
    nodeS.push(root);

    while(!idxS.empty()) {
        // get boundaries of current partition
        int left = idxS.top();
        idxS.pop();
        int right = idxS.top();
        idxS.pop();

        // update current root node's value
        int mid = left + (right - left) / 2;
        TreeNode *curNode = nodeS.top();
        curNode->value = nums[mid];
        nodeS.pop();

        int leftIdx = left;
        int rightIdx = mid - 1;

        // create left child
        if(leftIdx <= rightIdx) {
            curNode->leftNode = new TreeNode(0);
            nodeS.push(curNode->leftNode);

            idxS.push(rightIdx);
            idxS.push(leftIdx);
        }

        leftIdx = mid + 1;
        rightIdx = right;
        
        // create right child
        if(leftIdx <= rightIdx) {
            curNode->rightNode = new TreeNode(0);
            nodeS.push(curNode->rightNode);

            idxS.push(rightIdx);
            idxS.push(leftIdx);
        }
    }

    return root;
}


std::string maximalPalinfrome(std::string s) {
    std::map<char, int> charNum;

    int n = s.size();
    for (int i = 0; i < n; ++i) {
        charNum[s[i]]++;
    }

    int numOdd = 0;
    int sizeStr = 0;
    char smallestOddChar = 'a';
    for(auto& [c, num]: charNum) {
        if(num % 2 != 0) {
            ++numOdd;
            if(numOdd == 1) {
                smallestOddChar = c;
                sizeStr += num;
            } else {
                sizeStr += num - 1;
            }
        } else {
            sizeStr += num;
        }
    }

    std::string retStr(sizeStr, '0');
    
    int idx = 0;
    for (auto& [c, num]: charNum) {
        if(c == smallestOddChar || num % 2 == 0) {
            if(num % 2 == 1) {
                retStr[sizeStr / 2] = c;
                num--;
            }
            while(num > 0) {
                retStr[idx] = c;
                retStr[sizeStr - idx - 1] = c;
                num -= 2;
                ++idx;
            }
        } else {
            num--;
            while(num > 0) {
                retStr[idx] = c;
                retStr[sizeStr - idx - 1] = c;
                num -= 2;
                ++idx;
            }
        }
    }

    return retStr;
}


int calculateUsedBlock(std::vector<std::vector<int>> nums) {
    return 1;
}

float square(float nums[5]) {
    return nums[0]*nums[0] + nums[1]*nums[1] + nums[2]*nums[2]
             + nums[3]*nums[3] + nums[4]*nums[4]; 
}

float square2nums(float nums1[5], float nums2[5]) {
    return nums1[0]*nums2[0] + nums1[1]*nums2[1] + nums1[2]*nums2[2]
             + nums1[3]*nums2[3] + nums1[4]*nums2[4]; 
}

int main() {
    // std::vector<int> nums = {1, 6, 7};
    // // TreeNode *root = createBST(nums);
    // TreeNode *root = createBSTwithoutRecursion(nums);
    // std::queue<TreeNode*> s;
    // s.push(root);

    // while(!s.empty()) {
    //     int size = s.size();
    //     for(int i = 0; i < size; ++i) {
    //         TreeNode *curNode = s.front();
    //         s.pop();

    //         std::cout<<" "<<curNode->value;

    //         // store the children if exist
    //         if(curNode->leftNode) s.push(curNode->leftNode);
    //         if(curNode->rightNode) s.push(curNode->rightNode);
    //     }
    //     std::cout<<std::endl;
    // }

    // std::string s = "aaabb";
    std::string s = "aaabbbcc";
    std::string ans = maximalPalinfrome(s);

    std::cout<<"ans is:"<<ans<<std::endl;

    float nums1[5] = {30.67, 695.62, 6556.24, 2.980, 32.20};
    float nums2[5] = {3.00,	56.00,	792.00,	0,	0};

    float square1 = square(nums1);
    float square2 = square(nums2);
    float squareSum = square2nums(nums1, nums2);
    float cosine = squareSum / (sqrt(square1)*sqrt(square2));

    std::cout<<"cosine is: "<<cosine<<" squareSum:"<<squareSum<<" below: "<<sqrt(square1)*sqrt(square2)<<std::endl;

    return 1;
}