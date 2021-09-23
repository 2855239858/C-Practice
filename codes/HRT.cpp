#include <iostream>
#include "algorithm.h"
#include <string.h>
using namespace std;

int maxDistance(vector<int>& nums) {
    int n = nums.size();
    int down = 0;
    int up = 0;

    int maxDis = 0;
    for(int i = 1; i < n; ++i) {
        if(nums[i] < nums[i - 1]) {
            if(up != 0) {
                up = 0;
                down = 0;
                int cur = i - 1;
                while(cur > 0 && nums[cur] == nums[cur - 1]) {
                    ++down;
                    --cur;
                }
            }
            down++;
        } else if(nums[i] > nums[i - 1]) {
            up++;
        } else {
            if(up == 0) down++;
            else up++;
        }

        maxDis = max(maxDis, up + down + 1);
    }

    return maxDis;
}

    string isOneEditDistance(string s, string t) {
        int n1 = s.size();
        int n2 = t.size();
        
        if(abs(n1 - n2) > 1) return "IMPOSSIBLE";
        
        bool flag = false;
        string op;
        int i = 0, j = 0;
        while(i < n1) {
            if(s[i] != t[j]) {
                if(flag) return "IMPOSSIBLE";
                if(n1 > n2) {
                    j -= 1;
                    op = "DELETE " + string(1, s[i]);
                } else if(n1 < n2) {
                    i -= 1;
                    op = "ADD " + string(1, t[j]);
                } else {
                    if(i < n1 - 1) {
                        op = "SWAP " + string(1, s[i]);
                        op = op + " " + string(1, s[i + 1]);
                        swap(s[i], s[i + 1]);
                    } else {
                        return "IMPOSSIBLE";
                    }
                }
                flag = true;
            }
            ++i, ++j;
        }
        
        if(i != n1 || j != n2) {
            if(flag) return "IMPOSSIBLE";
            else if(i != n1) {
                op = "DELETE " + string(1, s[n1 - 1]);
            } else {
                op = "ADD " + string(1, t[n2 - 1]);
            }
        }
        
        return op;
    }


    int maxProduct(string s) {
        
        int n = s.size();
        int dp[n][n];
        memset(dp, 0, sizeof(dp));
        
        int map[n][n];
        memset(map, 0, sizeof(map));
        vector<pair<int, int>> subs;
        
        
        for(int i = n - 1; i >= 0; --i) {
            dp[i][i] = 1;
            map[i][i] = 1<<i;
            subs.push_back({1, map[i][i]});
            for(int j = i + 1; j < n; ++j) {
                if(s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                    map[i][j] = map[i + 1][j - 1] | (1<<i) | (1<<j);
                    subs.push_back({dp[i][j], map[i][j]});
                } else {
                    if(dp[i + 1][j] > dp[i][j - 1]) {
                        dp[i][j] = dp[i + 1][j];
                        map[i][j] = map[i + 1][j];
                    } else {
                        dp[i][j] = dp[i][j - 1];
                        map[i][j] = map[i][j - 1];
                    }
                }
            }
        }
        
        // sort(subs.begin(), subs.end());
        
        int ans = 0;
        int size = subs.size();
        for(int i = 0; i < size; ++i) {
            for(int j = i + 1; j < size; ++j) {
                if((subs[i].second & subs[j].second) == 0) {
                    cout<<"i: ("<<subs[i].first<<", "<<subs[i].second<<"), j: ("<<subs[j].first<<", "<<subs[j].second<<")"<<endl;
                    ans = max(ans, subs[i].first * subs[j].first);
                }
            }
        }
        
        return ans;
    }

class Solution {
public:
    int n = 0;
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        n = parents.size(); 
        vector<int> ans(n, 1);
        
        // children array
        vector<vector<int>> children(n);
        int valueToIdx[100002];
        memset(valueToIdx, 0xff, sizeof(valueToIdx));
        
        // init children and valueToIdx
        for(int i = 0; i < n; ++i) {
            int curIdx = i;
            if(parents[i] != -1) {
                children[parents[i]].push_back(i);
            }
            valueToIdx[nums[i]] = i;
        }
        
        int valueToLabel[100002], valueToLastChild[100002];
        memset(valueToLabel, 0xff, sizeof(valueToLabel));
        memset(valueToLastChild, 0xff, sizeof(valueToLastChild));
        
        int label = 0;
        preorderLabel(valueToLabel, valueToLastChild, 0, label, children, nums);
        
        if(valueToLabel[1] == -1) return ans;
        
        int child = valueToIdx[1];
        int num = 2;
        while(child != -1) {
            int value = nums[child];
            int left = valueToLabel[value];
            int right = valueToLastChild[value];
            int labelOfNum = valueToLabel[num];
            if(left <= labelOfNum && labelOfNum <= right) {
                ++num;
            } else {
                ans[child] = num;
                child = parents[child];
            }
        }
        
        return ans;
    }
    
    void preorderLabel(int* valueToLabel, int* valueToLastChild, int idx, int& label, vector<vector<int>>& children, vector<int>& nums) {
        valueToLabel[nums[idx]] = label++;
        
        for(auto& nextIdx: children[idx]) {
            preorderLabel(valueToLabel, valueToLastChild, nextIdx, label, children, nums);
        }
        
        valueToLastChild[nums[idx]] = label - 1;
    }
    
};

int findMaxJump(vector<int>& nums, int diff) {
    unordered_map<int, int> numToIndex;

    int n = nums.size();
    int dp[n];
    memset(dp, 0, sizeof(dp));

    int ans = 0;
    for(int i = 0; i < n; ++i) {
        auto itr = numToIndex.find(nums[i]);
        if(itr == numToIndex.end()) {
            numToIndex[nums[i]] = i;
            dp[i] = 1;
        } else {
            int lastIndex = numToIndex[nums[i]];
            if(i - lastIndex > diff) {
                dp[i] = dp[lastIndex] + 1;
                numToIndex[nums[i]] = i;
            } else {
                // dp[i] = dp[lastIndex];
            }
        }

        ans = max(ans, dp[i]);
    }

    return ans;
}

int findFullLine(vector<vector<int>> field, vector<vector<int>> figure) {
        int down[3];
        memset(down, 0, sizeof(down));
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                if(figure[j][i] == 1) {
                    down[i] = j;
                }
            }
        }
        
        for(int i = 0; i < 3; ++i){
            cout<<down[i]<<endl;
        }

        int row = field.size();
        int n = field.back().size() - 3;
        int m = field.back().size();
        for(int i = 0; i <= n; ++i) {
            int min_down = INT_MAX;
            for(int x = i; x < i + 3; ++x) {
                int height = row;
                for(int y = 0; y < row; ++y) {
                    if(field[y][x] == 1) {
                        height = y;
                        break;
                    }
                }
                int dis = height - down[x - i];
                min_down = min(min_down, dis);
            }
            
            if(min_down < 1) continue;
            bool ans = true;
            for(int x = min_down + 1; x >= min_down - 1; --x) {
                for(int y = 0; y < m; ++y) {
                    if(y >= i && y < i + 3) {
                        ans &= field[x][y] | figure[x - min_down + 1][y - i];
                    } else {
                        ans &= field[x][y];
                    }
                    if(!ans) break;
                }
                if(ans) return i;
            }
        }
        
        return -1;
}

int main() {
    // vector<int> test1 = {2, 6, 8, 5};
    // vector<int> test2 = {1, 5, 5, 2, 6};
    // vector<int> test3 = {1, 1};

    // cout<<"test 1: "<<maxDistance(test1)<<endl;
    // cout<<"test 2: "<<maxDistance(test2)<<endl;
    // cout<<"test 3: "<<maxDistance(test3)<<endl;


    // string test1S = "gain", test1T = "again";
    // string test2S = "parks", test2T = "park";
    // string test3S = "form", test3T = "from";
    // string test4S = "o", test4T = "odd";

    // cout<<"test 1: "<<isOneEditDistance(test1S, test1T)<<endl;
    // cout<<"test 2: "<<isOneEditDistance(test2S, test2T)<<endl;
    // cout<<"test 3: "<<isOneEditDistance(test3S, test3T)<<endl;
    // cout<<"test 4: "<<isOneEditDistance(test4S, test4T)<<endl;

    // string s = "zqz";
    // int max = maxProduct(s);
    // cout<<"Max product is: "<<max<<endl;

    // vector<int> parents = {-1,0,0,2};
    // vector<int> nums = {1,2,3,4};

    // Solution solution1;
    // vector<int> ans = solution1.smallestMissingValueSubtree(parents, nums);

    // for(int i = 0; i < ans.size(); ++i) {
    //     cout<<ans[i]<<" ";
    // }
    // cout<<endl;


    // vector<int> nums = {1, 3, 1, 1, 3, 1};
    // cout<<"ans is: "<<findMaxJump(nums, 0)<<endl;

    vector<vector<int>> field1 = {{0,0,0},{0,0,0},{0,0,0},{1,0,0},{1,1,0}};
    vector<vector<int>> figure1 = {{0,0,1},{0,1,1},{0,0,1}};

    vector<vector<int>> field2 = {{0,0,0,0,0}, 
                                {0,0,0,0,0}, 
                                {0,0,0,0,0}, 
                                {1,1,0,1,0}, 
                                {1,0,1,0,1}};
    vector<vector<int>> figure2 = {{1,1,1}, 
                                {1,0,1}, 
                                {1,0,1}};

    int ans1 = findFullLine(field1, figure1);
    int ans2 = findFullLine(field2, figure2);

    cout<<"ans1 is: "<<ans1<<endl;
    cout<<"ans2 is: "<<ans2<<endl;

    return 0;
}
