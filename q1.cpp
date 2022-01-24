#include <iostream>

using namespace std;

int parseInt(string input) {
    
    int res = 0;
    bool isNegative = false;

    int n = input.size();
    if (n == 0) {
        return res;
    }

    // judge whether is negative
    isNegative = (input[0] == '-') ? true: false;

    for (int i = isNegative ? 1: 0; i < n; ++i) {
        res = res * 10 + (input[i] - '0');
    }

    return isNegative ? -1 * res: res;
}

int main() {
    string input1 = "12345";
    string input2 = "-1234";

    cout<<parseInt(input1)<<endl;
    cout<<parseInt(input2)<<endl;

    return 0;
}