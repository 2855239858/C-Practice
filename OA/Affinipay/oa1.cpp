#include <iostream>

using namespace std;

string addTime(string time, int addition) {
    int hour = 0;
    int minute = 0;
    bool isAM = false;

    // read input hour and minute
    int index = 0;
    int n = time.size();
    while (index < n && time[index] != ':') {
        hour = hour * 10 + (time[index] - '0');
        ++index;
    }
    index += 1;
    while (index < n && time[index] != ' ') {
        minute = minute * 10 + (time[index] - '0');
        ++index;
    }
    // convert 12-hour to 24-hour
    isAM = time[++index] == 'A';
    if (isAM) {
        if (hour == 12) {
            hour = 0;
        }
    } else {
        if (hour != 12) {
            hour += 12;
        }
    }

    // convert hour:minute to total minute
    minute += hour * 60 + addition;
    // constraint minute in [0, 24 * 60)
    minute %= 24 * 60;
    if (minute < 0) {
        minute += 24 * 60;
    }
    
    // convert total minute to hour:minute
    hour = minute / 60;
    minute = minute % 60;

    // convert 24-hour to 12-hour
    if (hour < 12) {
        isAM = true;
        if (hour == 0) {
            hour = 12;
        }
    } else {
        isAM = false;
        if (hour != 12) {
            hour -= 12;
        }
    }

    string minuteStr = to_string(minute);
    return to_string(hour) + ":" + string(2 - minuteStr.size(), '0') + minuteStr + (isAM ? " AM": " PM");
}

int main() {
    cout<<addTime("12:13 AM", 0)<<endl;
    cout<<addTime("12:13 PM", 0)<<endl;
    cout<<addTime("9:13 AM", 200)<<endl;
    cout<<addTime("11:13 PM", 200)<<endl;
    cout<<addTime("0:43 AM", 200)<<endl;
    cout<<addTime("9:13 AM", -200)<<endl;
    cout<<addTime("9:13 AM", -25 * 60)<<endl;
    
    return 1;
}