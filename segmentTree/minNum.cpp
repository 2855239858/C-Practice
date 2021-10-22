// It's a template for sloving segment tree problems.

#include <iostream>
#include <math.h>

const int INFINITE = INT_MAX;

struct SegTreeNode
{
    int val;
    int mark;
};

SegTreeNode segTree[100];

void build(int root, int arr[], int start, int end) {
    segTree[root].mark = 0;
    if (start == end) {
        segTree[root].val = arr[start];
    } else {
        int mid = start + (end - start) / 2;
        int left = root * 2 + 1;
        int right = root * 2 + 2;

        build(left, arr, start, mid);
        build(right, arr, mid + 1, end);

        // (1) customized
        segTree[root].val = std::min(segTree[left].val, segTree[right].val);
        std::cout<<"root: "<<root<<" val: "<<segTree[root].val<<std::endl;
    }
}

void pushDown(int root) {
    if (segTree[root].mark != 0) {
        int left = root * 2 + 1;
        int right = root * 2 + 2;

        // (2) customized: how to delay update
        segTree[left].mark += segTree[root].mark;
        segTree[right].mark += segTree[root].mark;

        segTree[left].val += segTree[root].mark;
        segTree[right].val += segTree[root].mark;

        // reset mark to 0 after update
        segTree[root].mark = 0;
    }
}

// [ns, ne]: current segment
// [us, ue]: segment needed to update
void update(int root, int ns, int ne, int us, int ue, int addVal) {
    // no cross segment between current and update segment
    if (us > ne || ue < ns) {
        return;
    }

    if (us <= ns && ue >= ne) {
        segTree[root].val += addVal;
        segTree[root].mark += addVal;
        return;
    }
    pushDown(root);

    // only some parts of the cross segment
    int mid = ns + (ne - ns) / 2;
    int left = root * 2  + 1;
    int right = root * 2 + 2;

    update(left, ns, mid, us, ue, addVal);
    update(right, mid + 1, ne, us, ue, addVal);
    
    // backtrack to update current node
    segTree[root].val = std::min(segTree[left].val, segTree[right].val);
}

int query(int root, int ns, int ne, int qs, int qe) {
    // no cross segment
    if (qs > ne || qs < ns) {
        return INFINITE;
    }

    // current segment in query segment
    if (qs <= ns && qe >= ne) {
        return segTree[root].val;
    }
    pushDown(root);

    int mid = ns + (ne - ns) / 2;
    return std::min(query(root * 2 + 1, ns, mid, qs, qe),
                    query(root * 2 + 2, mid + 1, ne, qs, qe));
}


int main() {
    int nums[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    build(0, nums, 0, 9);

    std::cout<<"Query 1 (0, 9): "<<query(0, 0, 9, 0, 9)<<std::endl;
    std::cout<<"Query 2 (0, 4): "<<query(0, 0, 9, 0, 4)<<std::endl;
    std::cout<<"Query 3 (5, 9): "<<query(0, 0, 9, 5, 9)<<std::endl;

    update(0, 0, 9, 3, 6, -10);
    std::cout<<"Update 1 (3, 6, -10)"<<std::endl;
    std::cout<<"Query 4 (0, 9): "<<query(0, 0, 9, 0, 9)<<std::endl;
    std::cout<<"Query 5 (0, 4): "<<query(0, 0, 9, 0, 4)<<std::endl;
    std::cout<<"Query 6 (5, 9): "<<query(0, 0, 9, 5, 9)<<std::endl;

    return 0;
}