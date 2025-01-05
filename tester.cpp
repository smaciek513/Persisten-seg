#include <bits/stdc++.h>
#include "prev.h"

using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    init(a);

    int q;
    cin >> q;
    while(q--){
        int k;
        cin >> k;

        if(k){
            int i, lo, hi;
            cin >> i >> lo >> hi;
            cout << prevInRange(i, lo, hi) << "\n";
        }
        else{
            int value;
            cin >> value;
            pushBack(value);
        }
    }

    done();
    return 0;
}