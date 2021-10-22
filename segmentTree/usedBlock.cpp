#include <iostream>
#include <math.h>

const int INFINITE = INT_MAX;

struct SegmentTreeNode
{
    int val;
    int mark;
    int l;
    int r;
};

SegmentTreeNode segTree[100];

void build(int root, int ns, int ne) {
    segTree[root].mark = 0;
    if (ns == ne) {
        segTree[ns].val = 1;
        segTree[ns].l = ns;
        segTree[ns].r = ns;
    } else {
        int mid = ns + (ne - ns) / 2;
        int left = root * 2 + 1;
        int right = root * 2 + 2;

        build(left, ns, mid);
        build(right, mid + 1, ne);

        segTree[root].val = segTree[left].val + segTree[right].val;
        segTree[root].l = ns;
        segTree[root].r = ne;
    }
}

void pushDown(int root) {
    if (segTree[root].mark != 0) {
        int left = root * 2 + 1;
        int right = root * 2 + 2;

        segTree[left].val = segTree[left].r - segTree[left].l + 1;
        segTree[right].val = segTree[right].r - segTree[right].l + 1;

        segTree[left].mark = 1;
        segTree[right].mark = 1;

        segTree[root].mark = 0;
    }
}

void update(int root, int ns, int ne, int us, int ue) {
    if (us > ne || ue < ns) {
        return;
    }

    if (us <= ns && ue >= ne) {
        segTree[root].val = ne - ns + 1;
        segTree[root].mark = 1;
        return;
    }
    pushDown(root);

    int mid = ns + (ne - ns) / 2;
    int left = root * 2 + 1;
    int right = root * 2 + 2;
    update(left, ns, mid, us, ue);
    update(right, mid + 1, ne, us, ne);

    segTree[root].val = segTree[left].val + segTree[right].val;
}

int query(int root, int ns, int ne, int qs, int qe) {
    if (qs > ne || qe < ns) {
        return INFINITE;
    }

    if (qs <= ns && qe >= ne) {
        return segTree[root].val;
    }
    pushDown(root);

    int mid = ns + (ne - ns) / 2;

    return query(root * 2 + 1, ns, mid, qs, qe) +
            query(root * 2 + 2, mid + 1, ne, qs, qe);
}
