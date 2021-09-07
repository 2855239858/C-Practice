#pragma once
#include <iostream>
#include "algorithm.h"
#include <algorithm>
#include <cmath>
#include <string.h>
using namespace std;

#include <stack>

template<typename T, typename U> T my_max(T a,U b){
    return a > b ? a : b;
}

template<class T> class my_Max{
private:
    T a;
    T b;
public:
    my_Max(T a, T b);

    T which_bigger();
};

template<typename T> my_Max<T>::my_Max(T a, T b){
    this->a = a;
    this->b = b;
}

template<typename T> T my_Max<T>::which_bigger(){
    return this->a > this->b ? this->a : this->b;
}

uint32_t reverseBits(uint32_t n) {
    uint32_t ans = 0, digit = 1;
    for (int i = 0; i < 32; i++) {
        ans = (ans << 1) + (n & 1);
        n >>= 1;
    }
    
    return ans;
}

//合并区间
int merge_partition(vector<vector<int>>& intervals, int left, int right) {
    int l = left;
    cout<<right<<endl;
    int mid = intervals[right][0];
    for(int i = left; i < right; ++i) {
        if(intervals[i][0] <= mid) {
            // vector<int> tmp(intervals[i].begin(), intervals[i].end());
            // intervals[i][0] = intervals[l][0];
            // intervals[i][1] = intervals[l][1];
            // intervals[l][0] = tmp[0];
            // intervals[l][1] = tmp[1];
            // ++l;
            swap(intervals[i], intervals[l++]);
        }
    }
    
    // vector<int> tmp(intervals[right].begin(), intervals[right].end());
    // intervals[right][0] = intervals[l][0];
    // intervals[right][1] = intervals[l][1];
    // intervals[l][0] = tmp[0];
    // intervals[l][1] = tmp[1];
    swap(intervals[l], intervals[right]);
    return l;
}

void merge_quick_sort(vector<vector<int>>& intervals, int left, int right) {
    if(left >= right) return;
    
    int mid = merge_partition(intervals, left, right);
    merge_quick_sort(intervals, left, mid - 1);
    merge_quick_sort(intervals, mid + 1, right);
} 

vector<vector<int>> merge(vector<vector<int>>& intervals) {
    if(intervals.size() <= 1) return intervals;
    
    merge_quick_sort(intervals, 0, intervals.size() - 1);
    vector<vector<int>> ans;
    ans.push_back(intervals[0]);
    for(int i = 1; i < intervals.size(); ++i) {
        if(intervals[i][0] > (ans.back())[1]) {
            ans.push_back(intervals[i]);
        } else {
            ans.back()[1] = max(ans.back()[1], intervals[i][1]); 
        }
    }
    
    return ans;
}

//第k个排序
string getPermutation(int n, int k) {
    string ans = "";
    int cal = 1;
    vector<int> chs(n);
    for(int i = 1; i <= n; ++i) cal *= i;
    for(int i = 1; i <= n; ++i) chs[i - 1] = i;
    
    while(n) {
        cal /= n;
        int group = (k % cal == 0) ? (k / cal - 1) : (k / cal);
        k = (k >= cal) ? ((k % cal == 0) ? cal : k % cal) : k;
        
        ans += chs[group] + '0';
        cout<<chs[group]<<"-"<<ans<<endl;
        chs.erase(chs.begin() + group);
        --n;
    }
    
    return ans;
}

////////////////////////////////////////////////////////////////////////////////
// encode and decode
class De_Code_Solution {
public:
    int numDecodings_method1(string s) {
        if(s.size() == 0 || s[0] == '0') return 0;
        int ans = 0;
        int size = s.size();
        dfs(s, 0, ans, size);
        
        return ans;
    }
    
    void dfs(string& s, int index, int& ans, int& size) {
        if(index >= size) {
            ++ans;
            return;
        }
        if(s[index] == '0') {
            return;
        }
        
        dfs(s, index + 1, ans, size);
        if(s[index] <= '2' && index + 1 < size) {
            if(s[index] == '1' || s[index + 1] < '7') {
                dfs(s, index + 2, ans, size);
            }
        }
    }

    int numDecodings_method2(string s) {
        if(s.size() == 0 || s[0] == '0') return 0;
        int pre1 = 1, pre2 = 0;
        
        for(int i = 0; i < s.size(); ++i) {
            int cur = 0;
            if(s[i] != '0') cur += pre1;
            if(i != 0 && s[i - 1] != '0' && (s[i - 1] - '0') * 10 + (s[i] - '0') < 27) {
                cur += pre2;
            }
            pre2 = pre1;
            pre1 = cur;
        }
        
        return pre1;
    }
};

//////////////////////////////////////////////////////////////////////////////////
/// 单词拆分
class WordBreakSolution {
public:
    bool recur_wordBreak(string s, vector<string>& wordDict) {
        if(s.size() <= 0) return true;
        unordered_set<string> word_map(wordDict.begin(), wordDict.end());
        
        return partitionWord(s, word_map, 0);
    }
    
    bool partitionWord(string& s, unordered_set<string>& map, int start) {
        if(map.count(s.substr(start, s.size() - start))) return true;
        
        bool ans = false;
        for(int i = start; i < s.size(); ++i) {
            if(map.count(s.substr(start, i - start + 1))) {
                ans |= partitionWord(s, map, i + 1);
                if(ans == true) break;
            }
        }
        
        return ans;
    }

    bool dp_wordBreak(string s, vector<string>& wordDict) {
        if(s.size() <= 0) return true;
        unordered_set<string> map(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size(), false);
        dp[0] = true;
        
        for(int i = 1; i <= s.size(); ++i) {
            for(int j = 0; j < i && dp[i] == false; ++j) {
                dp[i] = dp[j] && map.count(s.substr(j, i - j));
            }
        }
        
        return dp[s.size()];
    }
};

///////////////////////////////////////////////////////////////////////////////
///basic calculator 2
class Calculator_2_Solution {
public:
    int calculate(string s) {
        int num = 0;
        char op = '+';
        vector<int> nums;
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == ' ') continue;
            else if(s[i] < '0' || s[i] > '9') {
                op = s[i];
            } else {
                while(s[i] <= '9' && s[i] >= '0') {
                    num = num * 10 + (s[i] - '0');
                    ++i;
                }
                if(op == '+') nums.push_back(num);
                else if(op == '-') nums.push_back(-num);
                else if(op == '*') nums.back() *= num;
                else if(op == '/') nums.back() /= num;
                num = 0, --i;
            }
        }
        num = 0;
        for(auto n : nums) {
            num += n;
        }
        
        return num;
    }
};

///////////////////////////////////////////////////////////////////////////////
////水壶问题

struct pair_hash
{
    template <class T1, class T2>
    size_t operator () (pair<T1, T2> const &pair) const
    {
        size_t h1 = hash<T1>()(pair.first); //用默认的 hash 处理 pair 中的第一个数据 X1
        size_t h2 = hash<T2>()(pair.second);//用默认的 hash 处理 pair 中的第二个数据 X2
        return h1 ^ h2;
    }
};

class Water_and_Jug_Solution {
public:
    bool canMeasureWater_method1(int jug1, int jug2, int target) {
        if(jug1 + jug2 < target) return false;
        else if(target == 0) return true;
        else if(jug1 == 0) return jug2 == target;
        else if(jug2 == 0) return jug1 == target;
        
        queue<pair<int, int>> water_queue;
        set<pair<int, int>> water_set;
        water_queue.push({0, 0});
        water_set.insert({0, 0});
        
        while(water_queue.size() > 0) {
            pair<int, int> top = water_queue.front();
            water_queue.pop();
            if(top.first == target || top.second == target || top.first + top.second == target) return true;
            
            set<pair<int, int>> tmp_set;
            tmp_set.insert({top.first, 0});
            tmp_set.insert({0, top.second});
            tmp_set.insert({top.first, jug2});
            tmp_set.insert({jug1, top.second});
            tmp_set.insert({min(jug1, top.first + top.second), (top.second < jug1 - top.first ? 0 : (top.second - (jug1 - top.first)))});
            tmp_set.insert({(top.first < jug2 - top.second) ? 0 : (top.first - (jug2 - top.second)), min(jug2, top.first + top.second)});
            
            for(auto s : tmp_set) {
                if(water_set.find(s) != water_set.end()) continue;
                water_queue.push(s);
                water_set.insert(s);
            }
        }
        
        return false;
    }

    bool canMeasureWater_method2(int jug1Capacity, int jug2Capacity, int targetCapacity) {
        if(jug1Capacity + jug2Capacity < targetCapacity) return false;
        else if(targetCapacity == 0) return true;
        else if(jug1Capacity == 0) return jug2Capacity == targetCapacity;
        else if(jug2Capacity == 0) return jug1Capacity == targetCapacity;
        
        int gcd = GCD(jug1Capacity, jug2Capacity);
        return targetCapacity % gcd == 0;
    }
    
    int GCD(int a, int b) {
        if(b == 0) return a;
        return GCD(b, a %  b);
    }
};

////////////////////////////////////////////////////////////////////////////////////////
///////字符串解码
class Decode_String_Solution {
public:
    string decodeString(string s) {
        stack<string> s_s;
        
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] != ']') s_s.push(string(1, s[i]));
            else {
                string repeat = "";
                int num = 0;
                while(s_s.top()[0] != '[') {
                    repeat = s_s.top() + repeat;
                    s_s.pop();
                }
                s_s.pop();
                while(!s_s.empty() && s_s.top().size() == 1 && s_s.top()[0] <= '9' && s_s.top()[0] >= '0') {
                    num = num * 10 + (s_s.top()[0] - '0');
                    s_s.pop();
                }
                string push_s = "";
                while(num > 0) {
                    push_s += repeat;
                    --num;
                }
                s_s.push(push_s);
            }
        }
        string ans = "";
        while(!s_s.empty()) {
            ans = s_s.top() + ans;
            s_s.pop();
        }
        
        return ans;
    }
};

class Find_Safe_State_Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        vector<int> ans;
        unordered_map<int, bool> map;
        unordered_map<int, bool> visited;
        
        for(int i = 0; i < graph.size(); ++i) {
            dfs_with_mem(ans, map, graph, visited, i);   
        }
        cout<<"ans size: "<<ans.size()<<endl;
        sort(&ans[0], &ans.back() + 1); //第二个为 ans.back()将不会对最后一个数进行排序
        sort(&*ans.begin(), &ans.back() + 1);
        
        return ans;
    }
    
    bool dfs_with_mem(vector<int>& ans, unordered_map<int, bool>& map, vector<vector<int>>& graph, unordered_map<int, bool>& visited, int index) {
        if(index >= graph.size() || (visited.find(index) != visited.end() && visited[index] == true)) {
            map[index] = false;
            return false;
        }
        if(map.find(index) != map.end()) return map[index];
        if(graph[index].size() <= 0) {
            ans.push_back(index);
            map[index] = true;
            return true;
        }
        bool re = true;
        visited[index] = true;
        for(int i = 0, size = graph[index].size(); i < size; ++i) {
            re &= dfs_with_mem(ans, map, graph, visited, graph[index][i]);
            if(!re) break;
        }
        visited[index] = false;
        if(re) {
            map[index] = true;
            ans.push_back(index);
            return true;
        }
        
        map[index] = false;
        return false;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////network delay time
class Network_Delay_Time_Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        // int inf = INT_MAX / 2;
        int map[n][n];
        // memset(map, 6000 * 100 + 1, sizeof(int) * n * n);
        memset(map, 0x3f, sizeof(int) * n * n);
        cout<<map[0][0]<<endl;
        
        for(int i = 0, row = times.size(); i < row; ++i) {
            map[times[i][0] - 1][times[i][1] - 1] = times[i][2];
        }
        uint8_t used[n];
        int dist[n];
        memset(used, 0, sizeof(uint8_t) * n);
        // memset(dist, 6000 * 100 + 1, sizeof(int) * n);
        memset(dist, 0x3f, sizeof(int) * n);
        dist[k - 1] = 0;
        
        for(int n : used) {
            cout<<n<<" ";
        }
        cout<<endl;
        for(int n : dist) {
            printf("%d ", n);
        }
        cout<<endl;

        for(int i = 0; i < n; ++i) {
            int min_index = -1;
            for(int j = 0; j < n; ++j) {
                if(used[j] == 0 && (min_index == -1 || dist[j] < dist[min_index])) {
                    min_index = j;
                }
            }
            used[min_index] = 1;
            for(int j = 0; j < n; ++j) {
                dist[j] = min(dist[j], dist[min_index] + map[min_index][j]);
            }
        }
        int ans = 0;
        for(int n : dist) {
            if(n > ans) ans = n;
        }
        
        return ans == 0x3f3f3f3f ? -1 : ans;
    }
};

//////////////////////////////////////////////////////////////////////////////////////////
///////////////环形数组是否存在
class Is_Circle_Array_Solution {
public:
    int size = 0;
    bool circularArrayLoop(vector<int>& nums) {
        size = nums.size();
        uint8_t is_circle[size];
        memset(is_circle, 0, sizeof(uint8_t) * size);
        
        for(int i = 0; i < size; ++i) {
            if(travel(nums, is_circle, i, nums[i] < 0, 0)) return true;
        }
        return false;
    }
    
    bool travel(vector<int>& nums, uint8_t* is_circle, int index, bool neg, int cnt) {
        if(is_circle[index]) return (is_circle[index] != 2) && (cnt > 1);
        // 0:未访问 1:访问 2：不满足 3：满足
        
        is_circle[index] = 1;
        if((nums[index] < 0 && neg == false) || (nums[index] > 0 && neg == true)) {
            is_circle[index] = 0;
            return false;
        }
        if(travel(nums, is_circle, ((index + nums[index]) % size + size) % size, neg, cnt + 1)) {
            is_circle[index] = 3;
            return true;
        }
        is_circle[index] = 2;
        return false;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////
/////////stars
class Stars_Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        int n = asteroids.size();
        vector<int> ans;
        
        for(int i = 1; i < n; ++i) {
            if(ans.size() == 0 || ans.back() * asteroids[i] >0) {
                ans.push_back(asteroids[i]);
            } else {
                if(ans.back() < 0) ans.push_back(asteroids[i]);
                else {
                    while(ans.size() > 0 && abs(asteroids[i]) > abs(ans.back()) && ans.back() * asteroids[i] < 0) {
                        ans.pop_back();
                    }
                    if(ans.size() == 0) ans.push_back(asteroids[i]);
                    else if(-asteroids[i] == ans.back()) ans.pop_back();
                }
            }
        }
        
        return ans;
    }
};


//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////等差数列子数组
class Arithmetic_Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        int ans = 0, cnt = 0, pre = INT_MAX;
        if(nums.size() < 3) return ans;
        
        for(int i = 0, n = nums.size(); i < n; ++i) {
            if(pre == INT_MAX || pre != nums[i] - nums[i - 1]) {
                // ans += power(2, cnt) - (cnt - 1) * cnt / 2 - cnt - 1;
                if(cnt > 2) ans += pow(2, cnt) - (cnt + 1) * cnt / 2 - 1;
                pre = nums[i] - nums[i - 1];
                cnt = 2;
            } else {
                cnt += 1;
            }
        }
        if(cnt > 2) ans += pow(2, cnt) - (cnt + 1) * cnt / 2 - 1;
        return ans;
    }
};

/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////// k站内最便宜的航班

class findCheapestPrice_Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        int dp[n];
        memset(dp, 0x3f, sizeof(dp));
        dp[src] = 0;
        
        int ans = 0x3f3f3f3f;
        for(int t = 0; t < k + 1; ++t) {
            int new_dp[n];
            memset(new_dp, 0x3f, sizeof(new_dp));
            for(auto route: flights) {
                int i = route[0], j = route[1], price = route[2];
                new_dp[j] = min(new_dp[j], dp[i] + price);
                // new_dp[j] = min(dp[j], dp[i] + price);
                // cout<<"src: "<<i<<" des: "<<j<<" prices: "<<price<<" --- dp[j]: "<<dp[j]<<" dp[i] + price: "<<dp[i] + price<<endl;
            }

            // for(int i = 0; i < n; ++i) cout<<" "<<new_dp[i];
            // cout<<endl;

            memcpy(dp, new_dp, sizeof(dp));
            ans = min(ans, dp[dst]);
        }
        
        return ans == 0x3f3f3f3f? -1: ans;
    }
};

class island_Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        queue<pair<int, int>> q1;
        int ans = 0;
        
        int n = grid.size(), m = grid[0].size();
        for(int i = grid.size() - 1; i >= 0; --i) {
            for(int j = grid[i].size() - 1; j >= 0; --j) {
                if(grid[i][j] == '1') {
                    ++ans;
                    q1.push({i, j});
                    while(q1.size() > 0) {
                        auto& pos = q1.front();
                        int x = pos.first, y = pos.second;
                        q1.pop();
                        grid[x][y] = '0';
                        
                        bool inside = x >= 0 && x < n && y >= 0 && y < m;
                        if(inside && grid[x + 1][y] == '1') q1.push({x + 1, y});
                        if(inside && grid[x][y + 1] == '1') q1.push({x, y + 1});
                        if(inside && grid[x - 1][y] == '1') q1.push({x - 1, y});
                        if(inside && grid[x][y - 1] == '1') q1.push({x, y - 1});
                    }
                }
            }
        }
        return ans;
    }
};

int main()
{
    ///////////////////////////////////////////////////////////////////////////
    //合并区间
    // vector<vector<int>> nums = {{4, 5}, {1, 4}, {0, 1}};
    // vector<vector<int>> ans = merge(nums);

    // for(int i = 0; i < ans.size(); ++i) {
    //     cout<<ans[i][0]<<"-"<<ans[i][1]<<endl;
    // }

    ///////////////////////////////////////////////////////////////////////////
    //第k个排序
    // cout<<getPermutation(3, 2)<<endl;

    ///////////////////////////////////////////////////////////////////////////
    //encode and decode
    // string s = "111111111111111111111111111111111111111111111";
    // clock_t start, end;
    // De_Code_Solution decode_solution;
    // start = clock();
    // int ans = decode_solution.numDecodings_method1(s);
    // end = clock();
    // double time_total = (end - start) * 1000 / CLOCKS_PER_SEC;
    // cout<<"Method 1 ans is: "<<ans<<", run time is: "<<time_total<<"ms"<<endl;

    // start = clock();
    // ans = decode_solution.numDecodings_method2(s);
    // end = clock();
    // time_total = (end - start) * 1000 / CLOCKS_PER_SEC;
    // cout<<"Method 2 ans is: "<<ans<<", run time is: "<<time_total<<"ms"<<endl;
    
    ///////////////////////////////////////////////////////////////////////////
    // 单词拆分
    // string s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaab";
    // vector<string> dic = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    // WordBreakSolution work_break_test;
    // clock_t start;
    // start = clock();
    // cout<<"Recursion method for word break, answer is: "<<work_break_test.recur_wordBreak(s, dic)<<", run time is: "<<(clock() - start) * 1000 / CLOCKS_PER_SEC<<endl;
    // start = clock();
    // cout<<"DP method for word break, answer is: "<<work_break_test.dp_wordBreak(s, dic)<<", run time is: "<<(clock() - start) * 1000 / CLOCKS_PER_SEC<<endl;

    // ////////////////////////////////////////////////////////////////////////////
    // /// basic calculator 2
    // string s = "3+2*2";
    // Calculator_2_Solution calculator_solution;
    // cout<<"Expresstion is: "<<s<<", ans is: "<<calculator_solution.calculate(s)<<endl;

    ///////////////////////////////////////////////////////////////////////////////
    //////水壶问题
    // clock_t start_t, end_t;
    // int jug1 = 104707, jug2 = 104711, target = 1;
    // Water_and_Jug_Solution wajS;
    // start_t = clock();
    // bool answer1 = wajS.canMeasureWater_method1(jug1, jug2, target);
    // end_t = clock();
    // cout<<"Water and jug problem, method 1 answer is: "<<answer1<<", time using is: "<<(end_t - start_t) * 1000 / CLOCKS_PER_SEC<<"ms"<<endl;
    // start_t = clock();
    // bool answer2 = wajS.canMeasureWater_method2(jug1, jug2, target);
    // end_t = clock();
    // cout<<"Water and jug problem, method 2 answer is: "<<answer2<<", time using is: "<<(end_t - start_t) * 1000 / CLOCKS_PER_SEC<<"ms"<<endl;

    ///////////////////////////////////////////////////////////////////////////////
    ///////字符串解码
    // Decode_String_Solution decoder;
    // cout<<"The string is: 3[a]2[bc]"<<", the answer is:"<<decoder.decodeString("3[a]2[bc]")<<endl;

    // string s = "aaaaaaaaaaaaaa";
    // for(int i = 0; i < s.size(); ++i) {
    //     cout<<i<<": "<<s[i] - 'a'<<endl;
    // }

    // vector<int> stack;
    // stack.push_back(1);
    // cout<<"push_back(1)"<<endl;
    // cout<<"Size: "<<stack.size()<<", stack back: "<<stack.back()<<" capacity: "<<stack.capacity()<<endl;
    // stack.resize(10);
    // for(int i = 2; i <= 10; ++i) stack[i - 1] = i;
    // cout<<"resize(10) --- {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}"<<endl;
    // cout<<"Size: "<<stack.size()<<", stack back: "<<stack.back()<<" capacity: "<<stack.capacity()<<endl;
    // for(int i = 0; i < stack.size(); ++i) cout<<stack[i]<<endl;
    // stack.pop_back();
    // cout<<"pop_back()"<<endl;
    // cout<<"Size: "<<stack.size()<<", stack back: "<<stack.back()<<" capacity: "<<stack.capacity()<<endl;
    // stack.erase(stack.begin() + 8);
    // cout<<"erase(stack.begin() + 8)"<<endl;
    // cout<<"Size: "<<stack.size()<<", stack back: "<<stack.back()<<" capacity: "<<stack.capacity()<<endl;
    // stack.reserve(5);
    // cout<<"reserve(5)"<<endl;
    // cout<<"Size: "<<stack.size()<<", stack back: "<<stack.back()<<" capacity: "<<stack.capacity()<<endl;
    // stack.resize(5);
    // cout<<"stack.resize(5)"<<endl;
    // cout<<"Size: "<<stack.size()<<", stack back: "<<stack.back()<<" capacity: "<<stack.capacity()<<endl;
    // stack.resize(0);
    // cout<<"resize(0)"<<endl;
    // cout<<"Size: "<<stack.size()<<", stack back: "<<stack.back()<<" capacity: "<<stack.capacity()<<", is empty: "<<stack.empty()<<endl;
    // stack.push_back(1);
    // cout<<"push_back(1)"<<endl;
    // cout<<"Size: "<<stack.size()<<", stack back: "<<stack.back()<<" capacity: "<<stack.capacity()<<", is empty: "<<stack.empty()<<endl;

    // vector<int> nums = {2, 2, 3, 4};
    // sort(nums.begin(), nums.end(), [](int& a, int& b) {
    //     return a < b;
    // });
    // for(auto n : nums) cout<<n<<endl;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////// Find eventual safe state
    // Find_Safe_State_Solution find;
    // // vector<vector<int>> graph = {{1,2},{2,3},{5},{0},{5},{},{}};
    // // vector<vector<int>> graph = {{},{0,2,3,4},{3},{4},{}};
    // vector<vector<int>> graph = {{0},{1,2,3,4},{1,3,4},{2,4},{2}};
    // vector<int> ans = find.eventualSafeNodes(graph);
    // for(int n : ans) {
    //     cout<<n<<" ";
    // }
    // cout<<endl;


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////Network delay time
    // vector<vector<int>> times = {{2,1,1},{2,3,1},{3,4,1}};
    // Network_Delay_Time_Solution delay_time;
    // delay_time.networkDelayTime(times, 4, 2);
    // // cout<<"Answer is: "<<delay_time.networkDelayTime(times, 4, 2)<<endl;

    // int nums1[10];
    // memset(nums1, 0x7f, sizeof(int) * 10);
    // for(int n : nums1) cout<<n<<" ";
    // cout<<endl;
    // int nums2[10];
    // memset(nums2, 0x81, sizeof(int) * 10);
    // for(int n : nums2) cout<<n<<" ";
    // cout<<endl;
    // int nums3[10];
    // memset(nums3, 0xff, sizeof(int) * 10);
    // for(int n : nums3) cout<<n<<" ";
    // cout<<endl;

    // cout<<int(0x80000001)<<endl;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////is circle array 
    // Is_Circle_Array_Solution is_circle;
    // vector<int> nums = {-1,-2,-3,-4,-5};
    // bool ans = is_circle.circularArrayLoop(nums);
    // cout<<"ans is: "<<ans<<endl;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////stars
    // Stars_Solution stars;
    // vector<int> a = {-2,-2,1,-2};
    // auto ans = stars.asteroidCollision(a);
    // for(int i = 0; i < ans.size(); ++i) {
    //     cout<<ans[i]<<' ';
    // }
    // cout<<endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////等差数列子数组
    // Arithmetic_Solution arithma;
    // vector<int> nums = {1, 2, 3, 4};
    // int ans = arithma.numberOfArithmeticSlices(nums);
    // cout<<"Nums is: [1, 2, 3, 4], answer is: "<<ans<<endl;


    // int tempA = 2;
    // int *ptrTempA = &tempA;
    // int *ptrTempB;
    // /*1.常规使用dclTempA为一个int *的指针*/
    // decltype(ptrTempA) dclTempA;
    // /*2.需要特别注意，表达式内容为解引用操作，dclTempB为一个引用，引用必须初始化，故编译不过*/
    // decltype(*ptrTempA) dclTempB = tempA;
    // decltype(*ptrTempB) declTempC = tempA;
    // dclTempB = 20;
    // cout<<tempA<<" "<<dclTempB<<endl;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////k站内最便宜的航班
    // findCheapestPrice_Solution find;
    // vector<vector<int>> prices = {{3,4,4},{2,5,6},{4,7,10},{9,6,5},{7,4,4},{6,2,10},{6,8,6},{7,9,4},{1,5,4},{1,0,4},
    //                                 {9,7,3},{7,0,5},{6,5,8},{1,7,6},{4,0,9},{5,9,1},{8,7,3},{1,2,6},{4,1,5},{5,2,4},
    //                                 {1,9,1},{7,8,10},{0,4,2},{7,2,8}};
    // cout<<"Cheapest price: "<<find.findCheapestPrice(10, prices, 6, 0, 7)<<endl;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////岛屿数量
    // island_Solution isIsland;
    // vector<vector<char>> map = {{'1','1','1','1','0'},{'1','1','0','1','0'},{'1','1','0','0','0'},{'0','0','0','0','0'}};
    // int ans = isIsland.numIslands(map);
    // cout<<ans<<endl;

    array<int, 26> arr1;
    array<int, 26> arr2{};

    for(int i = 0; i < arr1.size(); ++i) cout<<arr1[i]<<"  ";
    cout<<endl;
    for(int i = 0; i < arr2.size(); ++i) cout<<arr2[i]<<"  ";

    return 0;
}