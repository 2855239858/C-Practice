#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

void dfs(vector<vector<int>>& pattern, vector<pair<int, int>>& posList, vector<vector<int>>& visited, int num, int x, int y) {
    int row = pattern.size();
    int col = pattern.back().size();

    if (x < 0 || y < 0 || x >= row || y >= col || pattern[x][y] != num || visited[x][y] != 0) {
        return;
    }

    posList.push_back({x, y});
    visited[x][y] = 1;

    dfs(pattern, posList, visited, num, x + 1, y);
    dfs(pattern, posList, visited, num, x, y + 1);
    dfs(pattern, posList, visited, num, x - 1, y);
    dfs(pattern, posList, visited, num, x, y - 1);
}


void movePatterns(vector<vector<int>>& pattern, vector<vector<string>> operations) {
    int row = pattern.size();
    int col = pattern.back().size();
    
    vector<vector<int>> visited(row, vector<int>(col, 0));
    unordered_map<int, vector<vector<pair<int, int>>>> numToIndex;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            int curNum = pattern[i][j];
            if (curNum != 0 && visited[i][j] == 0) {
                vector<pair<int, int>> curNums;
                dfs(pattern, curNums, visited, curNum, i, j);
                numToIndex[curNum].push_back(curNums);
            }
        }
    }

    // for (auto [_, i]: numToIndex) {
    //     for (auto j: i) {
    //         for (auto k: j) {
    //             cout<<" "<<k.first<<"-"<<k.second<<" ";
    //         }
    //         cout<<endl;
    //     }
    // }

    int direction[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};

    for (auto i: operations) {
        int num = stoi(i[0]);
        char c = i[1][0];
        int d = -1;
        switch (c) {
            case 'R':
                d = 0;
                break;
            case 'U':
                d = 1;
                break;
            case 'L':
                d = 2;
                break;
            case 'D':
                d = 3;
                break;
            default:
                break;
        }

        vector<vector<pair<int, int>>>& groups = numToIndex[num];
        for (auto& nums: groups) {
            int canMove = true;

            vector<vector<bool>> map(row, vector<bool>(col, false));
            for (auto& p: nums) {
                map[p.first][p.second] = true;
            }

            // check if can move
            for (auto& p: nums) {
                int x = p.first + direction[d][0];
                int y = p.second + direction[d][1];

                if (x < 0 || x >= row || y < 0 || y >= col || (pattern[x][y] != 0 && !map[x][y])) {
                    canMove = false;
                    break;
                }
            }

            if (canMove) {
                // first set original pos to 0
                for (auto& p: nums) {
                    pattern[p.first][p.second] = 0;
                }

                // set new pos to move character
                for (auto& p: nums) {
                    int x = p.first + direction[d][0];
                    int y = p.second + direction[d][1];

                    pattern[x][y] = num;
                }

                // update charaters' pos
                for (auto& p: nums) {
                    p.first += direction[d][0];
                    p.second += direction[d][1];
                }
            }
            
        }

    }
}

int main() {
    vector<vector<int>> map = {{0,0,0,0,0,0,0,0},
                                {1,0,0,4,4,0,0,0},
                                {1,0,0,4,0,0,0,0},
                                {1,0,0,4,0,0,0,0},
                                {0,0,4,4,0,2,2,0},
                                {0,0,0,4,0,0,2,0},
                                {0,0,0,4,4,0,3,0},
                                {0,0,0,0,0,0,0,0}};
    vector<vector<string>> operations = {{"1","L"},
                                            {"2","D"},
                                            {"3","R"},
                                            {"1","U"}};

    movePatterns(map, operations);

    for (auto nums: map) {
        cout<<endl;
        for (auto num: nums) {
            cout<<num<<" ";
        }
    }

    return 0;
}