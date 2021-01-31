#include<iostream>
#include<ctime>
using namespace std;

int arrange(int single, int doub){
    long long up = 1, down = 1;
    
    for(int i = single + doub; i > single; i--){
        up *= i;
    }
    for(int i = doub; i > 0; i--){
        down *= i;
    }
    
    return up / down;
}

int rectCover1(int number) {
    if(number == 0) return 0;
    
    int doub = number / 2;
    int ans = 1;
    
    for(int i = 1; i <= doub; i++){
        ans += arrange(number - i * 2, i);
    }
    
    return ans;
}

int rectCover2(int number) {
    if(number == 0 || number == 1) return number == 0? 0: 1;
    if(number == 2) return 2;
    
    int pre1 = 1, pre2 = 2, ans;
    
    for(int i = 3; i <= number; i++)
    {
        ans = pre1 + pre2;
        pre1 = pre2;
        pre2 = ans;
    }
    
    return ans;
}

int main(void){
    clock_t myFstart, myFend, Fstart, Fend;
    int scale = 25;

    myFstart = clock();
    long long ans1 = rectCover1(scale);
    myFend = clock();

    Fstart = clock();
    long long ans2 = rectCover2(scale);
    Fend = clock();

    cout<<"我的方法答案："<<ans1<<endl<<"运行时间："<<(double)(myFend - myFstart)*1000/CLOCKS_PER_SEC<<"ms"<<endl;
    cout<<"标准方法答案："<<ans2<<endl<<"运行时间："<<(double)(Fend - Fstart)*1000/CLOCKS_PER_SEC<<"ms"<<endl;

    return -1;
}