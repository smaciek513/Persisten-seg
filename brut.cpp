#include <bits/stdc++.h>
#include "prev.h"

std::vector<int> a;

void init(const std::vector<int> &seq){ a = seq; }

int prevInRange(int i, int lo, int hi){
    for(int j = i; j >= 0; j--){
        if(a[j] >= lo && a[j] <= hi) return j;
    }
    return -1;
}

void pushBack(int value){ a.push_back(value); }
void done(){ a.clear(); }