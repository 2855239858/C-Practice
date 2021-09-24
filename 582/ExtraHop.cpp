#include <iostream>
#include <vector>
#include <queue>
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


int main() {
    std::vector<int> nums = {1, 6, 7};
    // TreeNode *root = createBST(nums);
    TreeNode *root = createBSTwithoutRecursion(nums);
    std::queue<TreeNode*> s;
    s.push(root);

    while(!s.empty()) {
        int size = s.size();
        for(int i = 0; i < size; ++i) {
            TreeNode *curNode = s.front();
            s.pop();

            std::cout<<" "<<curNode->value;

            // store the children if exist
            if(curNode->leftNode) s.push(curNode->leftNode);
            if(curNode->rightNode) s.push(curNode->rightNode);
        }
        std::cout<<std::endl;
    }

    return 1;
}