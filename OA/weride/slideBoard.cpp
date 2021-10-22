#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>
#include <string.h>

using namespace std;

bool isDone(string& s, int row, int col) {
    int mid = col / 2;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            int idx = i * row + j;
            if (j < mid) {
                if (s[idx] == '2') return false;
            } else {
                if (s[idx] == '1') return false;
            }
        }
    }

    return true;
}

int minMove(vector<string>& map) {
    int row = map[0][0] - '0';
    int col = map[0][2] - '0';

    int n = map.size();
    string chess = string(row * col, '0');

    int zeroX = -1, zeroY = -1;
    for (int i = 1; i < n; ++i) {
        int size = map[i].size();
        for (int j = 0; j < size; ++j) {
            chess[(i - 1) * col + j] = map[i][j];
            if (map[i][j] == '0') {
                zeroX = i - 1;
                zeroY = j;
            }
        }
    }

    if (zeroX == -1) return isDone(chess, row, col)? 0: -1;

    queue<string> chesses;
    queue<pair<int, int>> poses;
    unordered_set<string> exist;
    chesses.push(chess);
    poses.push({zeroX, zeroY});
    exist.insert(chess);

    int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    int cnt = 0;
    while (!chesses.empty()) {
        if (++cnt > 15) return -1;
        int size = chesses.size();

        for (int i = 0; i < size; ++i) {
            string& topChess = chesses.front();
            pair<int, int>& topPos = poses.front();
            int x = topPos.first, y = topPos.second;

            for (int i = 0; i < 4; ++i) {
                int newX = x + direction[i][0];
                int newY = y + direction[i][1];
                if (newX < 0 || newY < 0 || newX >= row || newY >= col) {
                    continue;
                }

                swap(topChess[x * col + y], topChess[newX * col + newY]);
                if (isDone(topChess, row, col)) {
                    return cnt;
                }
                if (exist.find(topChess) == exist.end()) {
                    chesses.push(topChess);
                    poses.push({newX, newY});
                }
                swap(topChess[x * col + y], topChess[newX * col + newY]);
            }

            chesses.pop();
            poses.pop();
        }
    }

    return -1;
}


int main() {
    // vector<string> map = {"4 4",
    //                         "1122",
    //                         "1101",
    //                         "1222",
    //                         "1122"};
    vector<string> map = {"2 2",
                            "21",
                            "21"};

    int ans = minMove(map);

    cout<<"Ans is: "<<ans<<endl;

    return 0;
}