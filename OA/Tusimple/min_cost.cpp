#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;


int cost(string& a, string& b) {
    int n1 = a.size();
    int n2 = b.size();

    if (n1 != n2) {
        return 0x3f3f3f3f;
    }

    int res = 0;
    for (int i = 0; i < n1; ++i) {
        if (a[i] != b[i]) {
            res += 1;
        }
    }

    return res;
}

int validPath(vector<vector<string>> input, vector<string> path) {
    vector<vector<int>> edges;
    unordered_map<string, int> node2Idx;
    unordered_map<int, string> idx2Node;

    for (vector<string>& edge : input) {
        if (node2Idx.find(edge[0]) == node2Idx.end()) {
            node2Idx[edge[0]] = edges.size();
            idx2Node[edges.size()] = edge[0];
            edges.push_back({});
        }

        if (node2Idx.find(edge[1]) == node2Idx.end()) {
            node2Idx[edge[1]] = edges.size();
            idx2Node[edges.size()] = edge[1];
            edges.push_back({});
        }

        edges[node2Idx[edge[0]]].push_back(node2Idx[edge[1]]);
        edges[node2Idx[edge[1]]].push_back(node2Idx[edge[0]]);
    }

    int n = edges.size();
    int *dp1 = new int[n];
    int *dp2 = new int[n];
    memset(dp1, 0x3f, sizeof(int) * n);

    for (int i = 0; i < n; ++i) {
        dp1[i] = cost(path[0], idx2Node[i]);
    }

    // for (int i = 0; i < n; ++i) {
    //     cout<<dp1[i]<<"-";
    // }
    // cout<<endl;

    int size = path.size();
    for (int i = 1; i < size; ++i) {
        memset(dp2, 0x3f, sizeof(int) * n);
        for (int j = 0; j < n; ++j) {
            for (int adj : edges[j]) {
                // cout<<path[i]<<"-"<<idx2Node[adj]<<"-"<<cost(path[i], idx2Node[adj])<<endl;
                dp2[j] = min(dp2[j], cost(path[i], idx2Node[j]) + dp1[adj]);
            }
        }
        swap(dp1, dp2);

    // for (int i = 0; i < n; ++i) {
    //     cout<<dp1[i]<<"-";
    // }
    // cout<<endl;
    }

    int res = INT_MAX;
    for (int i = 0; i < n; ++i) {
        res = min(res, dp1[i]);
    }

    delete []dp1;
    delete []dp2;

    return res;
}

int main() {

    vector<vector<string>> graph = {{"AAA", "BBB"}, {"AAA", "CCC"}};
    vector<string> path1 = {"BBB", "AAA", "CCC"};
    vector<string> path2 = {"BBB", "ABC", "CCC"};

    cout<<validPath(graph, path2)<<endl;

    return 0;
}