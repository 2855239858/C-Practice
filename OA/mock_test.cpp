/*
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

Example 1:
    Input: s = "3[a]2[bc]"
    Output: "aaabcbc"

Example 2:
    Input: s = "3[a2[c]]"
    Output: "accaccacc"

Example 3:
    Input: s = "2[abc]3[cd]ef"
    Output: "abcabccdcdcdef"

Example 4:
    Input: s = "abc3[cd]xyz"
    Output: "abccdcdcdxyz"

int in [1, 300]
smallcase letter, digit and square buckets '[' ']'
*/

// vector<vector<string>>
// if "abs" put into the vector.back()
// if "32" put into the vector.back()
// if '[' create a new vector bebind the current vector
// if ']' end the current vector, concatenate into the last vector

// time complexity O(n), n is the size of input string
// space complexity O(n)

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

// used to read continuous alpha letters
string readAlphas(string& s, int& idx) {
    int n = s.size();

    string res;
    while (idx < n && s[idx] >= 'a' && s[idx] <= 'z') {
        res.push_back(s[idx]);
        ++idx;
    }

    return res;
}

// used to read the continuous number
string readNumber(string& s, int& idx) {
    int n = s.size();

    string res;
    while (idx < n && s[idx] >= '0' && s[idx] <= '9') {
        res.push_back(s[idx]);
        ++idx;
    }

    return res;
}

// convert a vector into string
string convert(vector<string>& strs) {
    string res;
    int n = strs.size();
    for (int i = 0; i < n; ++i) {
        char head = strs[i][0];
        if (head >= 'a' && head <= 'z') {
            res = res + strs[i];
        } else {
            int num = stoi(strs[i]);
            i += 1;
            string curStr = strs[i];
            while (num > 0) {
                res = res + curStr;
                num -= 1;
            }
        }
    }

    return res;
}

string decodeString(string s) {
    int n = s.size();
    // can't have any decode
    if (n <= 1) {
        return s;
    }

    vector<vector<string>> strs;
    strs.push_back({});

    int i = 0;
    while (i < n) {
        // if alpha letter
        if (s[i] >= 'a' && s[i] <= 'z') {
            strs.back().push_back(readAlphas(s, i));
        } else if (s[i] >= '0' && s[i] <= '9') { // if number
            strs.back().push_back(readNumber(s, i));
        } else if (s[i] == '[') { // create a new vector
            strs.push_back({});
            i += 1;
        } else { // ']'
            i += 1;
            if (strs.size() > 1) {
                string curStr = convert(strs.back());
                strs.pop_back();
                strs.back().push_back(curStr);
            }
        }
    }

    return convert(strs[0]);
}

int main() {
    cout<<decodeString("3[a]2[bc]")<<endl;

    return 0;
}