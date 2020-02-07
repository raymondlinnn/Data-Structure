#include "dsets.h"

void DisjointSets::test() {
    // do nothing
}

void DisjointSets::addelements(int n) {
    for (int i = 0; i < n; ++i) {
        data.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    // base case
    if (data[elem] < 0) return elem;

    int parent = data[elem];
    int idx = find(parent);
    // compress
    data[elem] = idx;
    return idx;
}

void DisjointSets::setunion(int a, int b){
    int a_ = find(a);
    int b_ = find(b);

    if (a_ == b_) return;

    // union by size
    // |a_| >= |b|
    if (data[a_] <= data[b_]) {
        data[a_] += data[b_];
        data[b_] = a_;
    }else{
        data[b_] += data[a_];
        data[a_] = b_;
    }
}

int DisjointSets::size(int elem) {
    int idx = find(elem);
    return -data[idx];
}
