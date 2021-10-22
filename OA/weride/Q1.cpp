#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> diceNum(string s) {
    vector<int> nums;

    int n = s.size();
    for (int i = 0; i < n;) {
        while (i < n && s[i] == ' ') ++i;
        int next = i;
        while (next < n && s[next] != ' ') ++next;

        nums.push_back(stoi(s.substr(i, next - i)));
        i = next;
    }

    int acc = 0;
    unordered_set<int> exist;
    vector<vector<int>> ret(2, vector<int>());

    for (auto a: {nums[0], nums[4]}) {
        for (auto b: {nums[1], nums[3]}) {
            for (auto c: {nums[2], nums[5]}) {
                int sum = a + b + c;
                if (exist.find(sum) == exist.end()) {
                    exist.insert(sum);
                    ret[1].push_back(sum);
                    acc++;
                }
            }
        }
    }

    ret[0].push_back(acc);
    sort(ret[1].begin(), ret[1].end());

    return ret;
}

int main() {
    // string input = "6 4 1 5 2 3";
    string input = "1 1 1 1 1 1";
    // string input = "12 132 1121 133 -1213 0";

    vector<vector<int>> ans = diceNum(input);
    
    for (vector<int>& nums: ans) {
        for (int num: nums) {
            cout<<num<<" ";
        }
        cout<<endl;
    }

    return 0;
}