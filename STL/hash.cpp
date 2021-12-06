#include <iostream>
#include <vector>

using namespace std;

struct vectorHash{
    size_t operator () (const vector<int>& arr) {
        size_t ret = 0;
        for (int i = 0; i < arr.size(); ++i) {
            ret = (ret << 1) ^ hash<int>() (arr[i]);
        }

        return ret;
    }
};