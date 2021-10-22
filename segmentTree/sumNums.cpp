#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

struct SegmentTree
{
    int val = 0;
    int mark = 0;
};

SegmentTree segTree[10000];


void build(vector<int>& nums, int root, int L, int R) {
    if (L > R) return;
    
    if (L == R) {
        segTree[root].val = nums[L];
        segTree[root].mark = 0;
        return;
    }

    int left = root * 2 + 1;
    int right = root * 2 + 2;
    int mid = L + (R - L) / 2;

    build(nums, left, L, mid);
    build(nums, right, mid + 1, R);

    segTree[root].val = segTree[left].val + segTree[right].val;
    segTree[root].mark = 0;
}

int update(int root, int L, int R, int idx, int val) {
    if (idx < L || idx > R) {
        return 0;
    }

    if (L == R) {
        int tmp = segTree[root].val;
        segTree[root].val = val;
        return val - tmp;
    }

    int mid = L + (R - L) / 2;
    int left = root * 2 + 1;
    int right = root * 2 + 2;

    int tmp = segTree[root].val;
    if (idx <= mid) {
        segTree[root].val += update(left ,L , mid, idx, val);
    } else {
        segTree[root].val += update(right, mid + 1, R, idx, val);
    }

    return segTree[root].val - tmp;
}

int query(int root, int L, int R, int ql, int qr) {
    if (L > qr || R < ql) {
        return 0;
    }

    if (L >= ql && R <= qr) {
        return segTree[root].val;
    }

    int mid = L + (R - L ) / 2;
    int left = root * 2 + 1;
    int right = root * 2 + 2;

    if (qr < mid) {
        return query(left, L, mid, ql, qr);
    } else if (ql > mid) {
        return query(right, mid + 1, R, ql, qr);
    } else {
        return query(left, L, mid, ql, mid) + query(right, mid + 1, R, mid + 1, qr);
    }
}

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    build(nums, 0, 0, nums.size() - 1);

    for (int i = 0; i < 10; ++i) {
        cout<<segTree[i].val<<" ";
    }
    cout<<endl;

    cout<<"Query 1 (0, 9): "<<query(0, 0, 9, 0, 9)<<endl;
    cout<<"Query 2 (0, 4): "<<query(0, 0, 9, 0, 4)<<endl;
    cout<<"Query 3 (5, 9): "<<query(0, 0, 9, 5, 9)<<endl;

    update(0, 0, 9, 4, 100);
    cout<<"Query 1 (0, 9): "<<query(0, 0, 9, 0, 9)<<endl;
    cout<<"Query 2 (0, 4): "<<query(0, 0, 9, 0, 4)<<endl;
    cout<<"Query 3 (5, 9): "<<query(0, 0, 9, 5, 9)<<endl;

    return 0;
}
