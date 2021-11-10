#include <iostream>

#include <vector>
#include <list>
#include <unordered_map>

using namespace std;

class solution {
private:
    vector<int> checkPointIds;
    unordered_map<int, list<int>> checkpoints;
    unordered_map<int, list<int>::iterator> racers;
    unordered_map<int, int> racer2checkpoint;

public:
    void record(int racerId, int checkpointId) {
        // new checkpoint
        if (checkpoints.find(checkpointId) == checkpoints.end()) {
            checkPointIds.push_back(checkpointId);
            checkpoints[checkpointId] = list<int>();
        }
        if (racers.find(racerId) == racers.end()) {
            checkpoints[checkpointId].push_back(racerId);
            racers[racerId] = --checkpoints[checkpointId].end();
        } else {
            // remove from old checkpoint
            int preCheckpointId = racer2checkpoint[racerId];
            checkpoints[preCheckpointId].erase(racers[racerId]);

            // insert into new checkpoint
            checkpoints[checkpointId].push_back(racerId);
            racers[racerId] = --checkpoints[checkpointId].end();
        }
        racer2checkpoint[racerId] = checkpointId;
    }

    vector<int> getOrder() {
        vector<int> res;
        for (int i = checkPointIds.size() - 1; i >= 0; --i) {
            for (int racerId: checkpoints[checkPointIds[i]]) {
                res.push_back(racerId);
            }
        }

        return res;
    }
};

int main() {
    vector<vector<int>> records = {{1, 1},
                                    {2, 1},
                                    {3, 1},
                                    {3, 2},
                                    {2, 2}}; // order 3->2->1
    solution method;
    for (auto& record: records) {
        method.record(record[0], record[1]);
    }

    vector<int> ans = method.getOrder();
    for (int i = 0; i < ans.size(); ++i) {
        cout<<ans[i]<<" ";
    }
    cout<<endl;

    return 0;
}