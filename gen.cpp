#include <bits/stdc++.h>

using namespace std;
//#define INT_MIN -1e9
//#define INT_MAX 1e9
#define N 10'000

mt19937 rng(chrono::steady_clock().now().time_since_epoch().count());

int p(int a, int b){ return a + rng()%(b-a+1); }

void solve(){
    int n = p(1, N);
    cout << n << "\n";
    for(int i = 0; i < n; i++){
        cout << p(INT_MIN, INT_MAX) << " ";
    }
    cout << "\n";

    int q = p(0, N);
    cout << q << "\n";
    while(q--){
        int k = p(0, 1);
        cout << k << " ";
        if(k){
            int i = p(0, n-1), lo = p(INT_MIN, INT_MAX), hi = p(INT_MIN, INT_MAX);
            if(lo > hi) swap(lo, hi);
            cout << i << " " << lo << " " << hi << "\n";
        }
        else{
            int val = p(INT_MIN, INT_MAX);
            cout << val << "\n";
            n++;
        }
    }
}

int main(){
    solve();
    return 0;
}