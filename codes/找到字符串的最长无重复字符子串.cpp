#include<algorithm>
#include<unordered_map>
class Solution {
public:
    /**
     * 
     * @param arr int整型vector the array
     * @return int整型
     */
    int maxLength(vector<int>& arr) {
        // write code here
//         int max_len = 0,tmp = 0;
//         for(int right = 0;right < arr.size();right++){
//             int left = right - 1;
//             while(left >= 0 && arr[left] != arr[right]){
//                 left--;
//             }
//             max_len = (right - left) > max_len?(right - left):max_len;
//         }
//         return max_len;
        unordered_map<int, int> hash_map;
        int left = -1,max_len = 0;
        for(int right = 0;right < arr.size();right++){
            if(hash_map.count(arr[right]) != 0){
                left = max(left, hash_map[arr[right]]);
            }
            hash_map[arr[right]] = right;
            max_len = max(max_len,right-left);
        }
        
        return max_len;
    }
};