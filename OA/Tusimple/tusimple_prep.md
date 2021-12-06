> 有一张无向图（地图），每个节点代表一个城市，每个城市的名字都由三个大写字母组成，比如AAA, BBB, CCC.
>给定一条路径，如果能够在地图中成功走这条路，则是一个valid path，返回0;
> 如果不能，则要把invalid path变成valid path，并返回一个最小的cost值。
>
>   先给定一个地图：
>                    AAA
>                /            \
>          BBB             CCC
>      三个城市。
>      valid path的例子：
>              AAA->BBB is valid.
>              BBB->AAA->CCC is valid.
>              CCC->AAA->CCC is valid.
>      有哪些情况是invalid path？
>      情况1： path中的某些城市在地图里面根本就没有出现，比如BBB->ABC->CCC.
>                  ABC根本没有在地图里面出现，代价就是可以把ABC改成AAA，改变了两个字母，代价是2.
>      情况2： path在地图中没有连通，比如BBB->CCC，是不可达的，可以把CCC改成AAA, 代价是3.

```c++
class Solution {
public:
    inline int cost(string &lhs, string &rhs) {
        int len = lhs.length();
        int res = 0;
        for (int i = 0; i < len; ++i) {
            if (lhs[i] != rhs[i]) {
                res++;
            }
        }
        return res;
    }

    int validPath(vector<vector<string>> input, vector<string> path) {
        unordered_map<string, int> vertices;
        unordered_map<int, string> invVertices;
        vector<vector<int>> graph;
        int idx = 0;
        for (auto &vec : input) {
            if (!vertices.count(vec[0])) {
                invVertices[idx] = vec[0];
                vertices[vec[0]] = idx++;
            }
            if (!vertices.count(vec[1])) {
                invVertices[idx] = vec[1];
                vertices[vec[1]] = idx++;
            }
            if (graph.size() <= vertices[vec[0]]) graph.emplace_back();
            graph[vertices[vec[0]]].push_back(vertices[vec[1]]);
            if (graph.size() <= vertices[vec[1]]) graph.emplace_back();
            graph[vertices[vec[1]]].push_back(vertices[vec[0]]);
        }
        int pLen = path.size();
        vector<vector<int>> dp(pLen, vector<int>(idx, INT_MAX));
        for (int j = 0; j < idx; ++j) {
            dp[0][j] = cost(path[0], invVertices[j]);
        }
        for (int i = 1; i < pLen; ++i) {
            for (int j = 0; j < idx; ++j) {
                for (int &neigh : graph[j]) {
                    dp[i][j] = min(dp[i][j], dp[i - 1][neigh] + cost(path[i], invVertices[j]));
                }
            }
        }
        int mi = INT_MAX;
        for (int j = 0; j < idx; ++j) {
            mi = min(mi, dp[pLen - 1][j]);
        }
        return mi;
    }
};
```

> Knight Dialer

```c++
const int MOD = 1e9 + 7;

class Solution {
public:
    int knightDialer(int n) {
        vector<vector<int>> to = {
           {4, 6},
            {6, 8},
            {7, 9},
            {4, 8},
            {0, 3, 9},
            {},
            {0, 1, 7},
            {2, 6},
            {1, 3},
            {2, 4}
        };
        vector<int> vec(10, 1);
        for (int iter = 1; iter < n; ++iter) {
            vector<int> tmp(10, 0);
            for (int i = 0; i < 10; ++i) {
                for (int& t : to[i]) {
                    tmp[t] += vec[i] % MOD; 
                    tmp[t] %= MOD;
                }
            }
            vec = tmp;
        }
        int res = 0;
        for (int& i : vec) {
            res += i % MOD;
            res %= MOD;
        }
        return res;
    }
};
```

> Sliding Window Maximum

```c++
class Solution {
public:
    inline void monoPush(deque<int> &que, vector<int>& nums, int idx) {
        while (!que.empty() && nums[que.back()] <= nums[idx]) {
            que.pop_back();
        }
        que.push_back(idx);
    }
    
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> que;
        vector<int> res;
        int len = nums.size();
        for (int i = 0; i < k; ++i) {
            monoPush(que, nums, i);
        }
        res.push_back(nums[que.front()]);
        for (int i = k; i < len; ++i) {
            if (que.front() <= i - k) que.pop_front();
            monoPush(que, nums, i);
            res.push_back(nums[que.front()]);
        }
        return res;
    }
};
```

> Sliding Window Median

```c++
class Solution {
public:
    inline void balance(multiset<int> &lo, multiset<int> &hi) {
        while (lo.size() > hi.size()) {
            hi.insert(*--lo.end());
            lo.erase(--lo.end());
        }
        while (hi.size() > lo.size() + 1) {
            lo.insert(*--hi.end());
            hi.erase(--hi.end());
        }
        while (!lo.empty() && *hi.begin() < *--lo.end()) {
            hi.insert(*--lo.end());
            lo.erase(--lo.end());
            lo.insert(*hi.begin());
            hi.erase(hi.begin());
        }
    }
    
    inline void calc(vector<double>& res, multiset<int> &lo, multiset<int> &hi) {
        if (lo.size() != hi.size()) {
            res.push_back(*hi.begin());
        } else {
            res.push_back((*--lo.end() * 1.0 + *hi.begin() * 1.0) * 0.5);
        }
    }
    
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        multiset<int> lo, hi;
        int len = nums.size();
        vector<double> res;
        for (int i = 0; i < k; ++i) {
            lo.insert(nums[i]);
        }
        balance(lo, hi);
        calc(res, lo, hi);
        for (int i = k; i < len; ++i) {
            if (lo.count(nums[i - k])) lo.erase(lo.find(nums[i - k]));
            else hi.erase(hi.find(nums[i - k]));
            lo.insert(nums[i]);
            balance(lo, hi);
            calc(res, lo, hi);
        }
        return res;
    }
};
```

> Shortest Path to Get All Keys

```c++
class Solution {
public:
    int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    inline int makeState(int x, int y, int st) {
        int res = 0 | x << 16 | y << 8 | st;
        return res;
    }

    inline vector<int> parseState(int state) {
        int x = state >> 16;
        int y = (((1 << 16) - 1) & state) >> 8;
        int st = ((1 << 8) - 1) & state;
        return vector<int>{x, y, st};
    }

    inline bool inRange(int x, int y, int m, int n) {
        return x >= 0 && x < m && y >= 0 && y < n;
    }

    int shortestPathAllKeys(vector<string>& grid) {
        queue<int> que;
        int m = grid.size();
        int n = grid[0].size();
        int keys = 0;
        vector<vector<vector<bool>>> vis(m, vector<vector<bool>>(n, vector<bool>(64)));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '@') {
                    que.push(makeState(i, j, 0));
                    vis[i][j][0] = true;
                }
                if (grid[i][j] >= 'a' && grid[i][j] <= 'f') {
                    keys |= (1 << (grid[i][j] - 'a'));
                }
            }
        }
        int cnt = 0;
        int sz = que.size();
        while (!que.empty()) {
            for (int i = 0; i < sz; ++i) {
                vector<int> state = parseState(que.front());
                // cout << state[0] << " " << state[1] << " " << state[2] << " " << cnt << endl;
                que.pop();
                for (auto &dir: dirs) {
                    int x = state[0] + dir[0];
                    int y = state[1] + dir[1];
                    int st = state[2];
                    if (!inRange(x, y, m, n)) continue;
                    if (grid[x][y] == '#') continue;
                    if (grid[x][y] >= 'a' && grid[x][y] <= 'f') {
                        st |= (1 << (grid[x][y] - 'a'));
                    } else if (grid[x][y] >= 'A' && grid[x][y] <= 'F') {
                        if (!(st & (1 << (grid[x][y] - 'A')))) {
                            continue;
                        }
                    }
                    if (st == keys) {
                        return cnt + 1;
                    }
                    if (vis[x][y][st]) continue;
                    vis[x][y][st] = true;
                    que.push(makeState(x, y, st));
                }
            }
            cnt++;
            sz = que.size();
        }
        return -1;
    }
};
```

> Combination Sum

```c++
class Solution {
public:
    inline void dfs(vector<int>& candidates, vector<int>& cur, vector<vector<int>> &res, int sum, int target, int start) {
        if (sum > target) {
            return;
        }
        if (sum == target) {
            res.push_back(cur);
        }
        int len = candidates.size();
        for (int i = start; i < len; ++i) {
            int num = candidates[i];
            cur.push_back(num);
            dfs(candidates, cur, res, sum + num, target, i);
            cur.pop_back();
        }
    }
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> cur;
        vector<vector<int>> res;
        dfs(candidates, cur, res, 0, target, 0);
        return res;
    }
};
```

> Partition to K Equal Sum Subsets  

```c++
class Solution {
public:
    inline bool dfs(vector<int>& nums, int cur, int selected, int &sum, int index) {
        int len = nums.size();
        if (selected == (1 << len) - 1) {
            return true;
        }
        for (int i = index; i < len; ++i) {
            if (!((1 << i) & selected)) {
                int tmp = cur + nums[i];
                if (tmp > sum) continue;
                if (tmp == sum) {
                    tmp = 0;
                    index = 0;
                }
                if (dfs(nums, tmp, (1 << i) | selected, sum, index + 1)) return true;
            }
        }
        return false;
    }
    
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int total = 0;
        int len = nums.size();
        for (int i = 0; i < len; ++i) {
            total += nums[i];
        }
        if (total % k != 0) {
            return false;
        }
        int sum = total / k;
        sort(nums.begin(), nums.end(), greater<int>());
        vector<bool> vis((1 << 16) - 1, false);
        return dfs(nums, 0, 0, sum, 0);
    }
};
```

> Meeting Rooms II

```c++
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end(), [](const vector<int> &lhs, const vector<int> &rhs) {
            return lhs[1] < rhs[1];
        });
        multiset<int> s;
        s.insert(intervals[0][1]);
        int len = intervals.size();
        for (int i = 1; i < len; ++i) {
            auto &vec = intervals[i];
            // find the first element greater than current
            auto iter = s.upper_bound(vec[0]);
            if (iter == s.begin()) {
                s.insert(vec[1]);
            } else {
                int num = *(--iter);
                s.erase(s.find(num));
                s.insert(vec[1]);
            }
        }
        return s.size();
    }
};
```
/////////////////////////////////////////////////
> segments intersection

![img](https://images2015.cnblogs.com/blog/962849/201612/962849-20161224213308323-370353362.png)

```c++
struct point()
{
    double x,y;
};
double multi(point a,point b,point c)//abxac,ab(b.x-a.x,b.y-a.y),ac(c.x-a.x,c.y-a.y)
{
    return (b.x-a.x)*(c.y-a.y)-(b.y-a.y)*(c.x-a.x);
}
bool isintersected(point a,point b,point c,point d)//判断两条线段是否相交
{
    double u,v,w,z;
    u=multi(a,b,c);
    v=mutil(a,b,d);
    w=mulit(c,d,b);
    z=multi(c,d,a);
    return (u*v<=0.00000001&&w*z<=0.00000001)//1相交0不相交
}
```

> Car Fleet

```c++
class Solution {
public:
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<vector<int>> sortPos;
        int len = position.size();
        for (int i = 0;  i < len; ++i) {
            sortPos.push_back(vector<int>{position[i], i});
        }
        sort(sortPos.begin(), sortPos.end(), greater<>());
        int cnt = 1;
        int curIdx = 0;
        for (int i = 1; i < len; ++i) {
            double time = (target - sortPos[curIdx][0]) * 1.0 / speed[sortPos[curIdx][1]];
            // cout << i << " " << time << " " << sortPos[i][0] + speed[sortPos[i][1]] * time << " " << target << endl;
            if (sortPos[i][0] + speed[sortPos[i][1]] * time - target >= -1E-4) {
                // pass
            } else {
                cnt++;
                curIdx = i;
            }
        }
        return cnt;
    }
};
```

> Count Unique Characters of All Substrings of a Given String

```c++
class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.size();
        if (n <= 1) {
            return n;
        }
        
        int indexes[26][2];
        memset(indexes, -1, sizeof (indexes));
        int res = 0;
        
        for (int i = 0; i < n; ++i) {
            int curIdx = s[i] - 'A';
            res += (indexes[curIdx][1] - indexes[curIdx][0]) * (i - indexes[curIdx][1]);
            indexes[curIdx][0] = indexes[curIdx][1];
            indexes[curIdx][1] = i;
        }
        
        for (int i = 0; i < 26; ++i) {
            res += (n - indexes[i][1]) * (indexes[i][1] - indexes[i][0]);
        }
        
        return res;
    }
};
```

> lowest common ancestor

```c++
class Solution {
public:
    bool dfs(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode* &res) {
        if (!root) return 0; 
        int cnt = 0;
        if (root == p || root == q) cnt++;
        if (dfs(root -> left, p, q, res)) cnt++;
        if (res) return cnt;
        if (dfs(root -> right, p, q, res)) cnt++;
        if (res) return cnt;
        if (cnt == 2) {
            res = root;
        }
        return cnt;
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* res = nullptr;
        dfs(root, p, q, res);
        return res;
    }
};
```

> Find the Kth Smallest Sum of a Matrix With Sorted Rows

```c++
#define piv pair<int, vector<int>>

class Solution {
public:
    inline string hash(vector<int> set) {
        string s;
        for (auto & i : set) {
            s += to_string(i);
        }
        return s;
    }

    int kthSmallest(vector<vector<int>>& mat, int k) {
        int m = mat.size();
        int n = mat[0].size();
        unordered_set<string> set;
        auto cmp = [](const piv &lhs, const piv &rhs) {
            return lhs.first > rhs.first;
        };
        priority_queue<piv, vector<piv>, decltype(cmp)> que(cmp);
        vector<int> init(m, 0);
        int sum = 0;
        for (int i = 0; i < m; ++i) {
            sum += mat[i][0];
        }
        que.push(piv{sum, init});
        set.insert(hash(init));
        int cum = k;
        while (!que.empty()) {
            auto front = que.top();
            auto vec = front.second;
            int sum = front.first;
            if (--cum == 0) return sum;
            que.pop();
            for (int i = 0; i < m; ++i) {
                vector<int> newVec = vec;
                int newSum = sum;
                newSum -= mat[i][newVec[i]];
                newVec[i]++;
                if (newVec[i] >= n) continue;
                newSum += mat[i][newVec[i]];
                string h = hash(newVec);
                if (!set.count(h)) {
                    que.push(piv{newSum, newVec});
                    set.insert(h);
                }
            }
        }
        return -1;
    }
};
```

> Find and Replace Pattern

```c++
class Solution {
public:
    inline bool match(const string &lhs, const string &rhs) {
        vector<int> to(26, -1);
        vector<int> from(26, -1);
        int len = lhs.length();
        for (int i = 0; i < len; ++i) {
            int f = lhs[i] - 'a';
            int t = rhs[i] - 'a';
            if (from[f] == -1 || from[f] == t) {
                from[f] = t;
            } else {
                return false;
            }
            if (to[t] == -1 || to[t] == f) {
                to[t] = f;
            } else {
                return false;
            }
        }
        return true;
    }
    
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<string> res;
        for (auto &string : words) {
            if (match(string, pattern)) {
                res.push_back(string);
            }
        }
        return res;
    }
};
```

> Regular expression matching

```c++
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.length();
        int n = p.length();
        if (m == 0 && n == 0) return true;
        if (n == 0) return false;
        int dp[m + 1][n + 1];
        dp[0][0] = 1;
        for (int i = 1; i <= m; ++i) dp[i][0] = 0;
        dp[0][1] = 0;
        for (int j = 1; j <= n; ++j) dp[0][j] = (p[j-1] == '*' && dp[0][j-2]);
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j-1] == '.' || s[i-1] == p[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else if (p[j-1] == '*') {
                    dp[i][j] = dp[i][j-2] || ((p[j-2] == s[i-1] || p[j-2] == '.') && dp[i-1][j]);
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        return dp[m][n];
    }
};
```

> Distinct subsequences

```c++
class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.length();
        int n = t.length();
        vector<vector<int>> dp(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            dp[i][0] = (s[i] == t[0]);
        }
        for (int j = 1; j < n; ++j) {
            long long sum = 0;
            for (int i = 0; i < m; ++i) {
                if (s[i] == t[j]) {
                    dp[i][j] = sum;
                }
                sum += dp[i][j - 1];
            }
        }
        int res = 0;
        for (int i = 0; i < m; ++i) {
            res += dp[i][n - 1];
        }
        return res;
    }
};

class Solution {
public:
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        if (m < n) {
            return 0;
        }
        
        int res = 0;
        ull dp[m + 0][n + 0];
        memset(dp, 0, sizeof(dp));
        
        for (int i = 0; i < m; ++i) {
            if (s[i] == t[0]) {
                dp[i][0] = 1;
            }
        }
        
        for (int j = 1; j < n; ++j) {
            ull sum = 0;
            char c1 = t[j];
            for (int i = j - 1; i < m; ++i) {
                char c2 = s[i];
                if (c1 == c2) {
                    dp[i][j] = sum;
                }
                sum += dp[i][j - 1];
            }
        }
        for (int i = 0; i < m; ++i) {
            res += dp[i][n - 1];
        }
        
        return res;
    }
};
```

> Sliding puzzle

```c++
class Solution {
private:
    vector<vector<int>> neighbors = {{1, 3}, {0, 2, 4}, {1, 5}, {0, 4}, {1, 3, 5}, {2, 4}};

public:
    int slidingPuzzle(vector<vector<int>>& board) {
        // 枚举 status 通过一次交换操作得到的状态
        auto get = [&](string& status) -> vector<string> {
            vector<string> ret;
            int x = status.find('0');
            for (int y: neighbors[x]) {
                swap(status[x], status[y]);
                ret.push_back(status);
                swap(status[x], status[y]);
            }
            return ret;
        };

        string initial;
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 3; ++j) {
                initial += char(board[i][j] + '0');
            }
        }
        if (initial == "123450") {
            return 0;
        }

        queue<pair<string, int>> q;
        q.emplace(initial, 0);
        unordered_set<string> seen = {initial};

        while (!q.empty()) {
            auto [status, step] = q.front();
            q.pop();
            for (auto&& next_status: get(status)) {
                if (!seen.count(next_status)) {
                    if (next_status == "123450") {
                        return step + 1;
                    }
                    q.emplace(next_status, step + 1);
                    seen.insert(move(next_status));
                }
            }
        }

        return -1;
    }
};
```

> Next permutaion

```c++
public class Solution {
    public void nextPermutation(int[] nums) {
        int i = nums.length - 2;
        while (i >= 0 && nums[i + 1] <= nums[i]) {
            i--;
        }
        if (i >= 0) {
            int j = nums.length - 1;
            while (nums[j] <= nums[i]) {
                j--;
            }
            swap(nums, i, j);
        }
        reverse(nums, i + 1);
    }

    private void reverse(int[] nums, int start) {
        int i = start, j = nums.length - 1;
        while (i < j) {
            swap(nums, i, j);
            i++;
            j--;
        }
    }

    private void swap(int[] nums, int i, int j) {
        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }
}
```

> Trap water

```c++
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0, current = 0;
        stack<int> st;
        while (current < height.size()) {
            while (!st.empty() && height[current] > height[st.top()]) {
                int top = st.top();
                st.pop();
                if (st.empty())
                    break;
                int distance = current - st.top() - 1;
                int bounded_height = min(height[current], height[st.top()]) - height[top];
                ans += distance * bounded_height;
            }
            st.push(current++);
        }
        return ans;
    }
};
```

> Merge interval

```c++
bool cmp(vector<int> &a, vector<int> &b) {
    return a[0] < b[0];
}

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        vector<vector<int>> res;
        sort(intervals.begin(), intervals.end(), cmp);
        int size = intervals.size();
        for (int i = 0; i < size; ++i) {
            if (res.size() > 0) {
                auto last = res[res.size() - 1];
                if (intervals[i][0] <= last[1]) {
                    res[res.size() - 1][1] = max(res[res.size() - 1][1], intervals[i][1]);
                    continue;
                }
            }
            res.push_back(intervals[i]);
        }
        return res;
    }
};
```

> Flip matrix 

```c++
class Solution {
private:
    static constexpr int dirs[5][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {0, 0}};

public:
    int encode(const vector<vector<int>>& mat, int m, int n) {
        int x = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                x = x * 2 + mat[i][j];
            }
        }
        return x;
    }

    vector<vector<int>> decode(int x, int m, int n) {
        vector<vector<int>> mat(m, vector<int>(n));
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                mat[i][j] = x & 1;
                x >>= 1;
            }
        }
        return mat;
    }

    void convert(vector<vector<int>>& mat, int m, int n, int i, int j) {
        for (int k = 0; k < 5; ++k) {
            int i0 = i + dirs[k][0], j0 = j + dirs[k][1];
            if (i0 >= 0 && i0 < m && j0 >= 0 && j0 < n) {
                mat[i0][j0] ^= 1;
            }
        }
    }

    int minFlips(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        int x_start = encode(mat, m, n), step = 0;
        if (x_start == 0) {
            return step;
        }

        unordered_set<int> visited;
        queue<int> q;
        visited.insert(x_start);
        q.push(x_start);

        while (!q.empty()) {
            ++step;
            int k = q.size();
            for (int _ = 0; _ < k; ++_) {
                vector<vector<int>> status = decode(q.front(), m, n);
                q.pop();
                for (int i = 0; i < m; ++i) {
                    for (int j = 0; j < n; ++j) {
                        convert(status, m, n, i, j);
                        int x_cur = encode(status, m, n);
                        if (x_cur == 0) {
                            return step;
                        }
                        if (!visited.count(x_cur)) {
                            visited.insert(x_cur);
                            q.push(x_cur);
                        }
                        convert(status, m, n, i, j);
                    }
                }
            }
        }

        return -1;
    }
};
```

