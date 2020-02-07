#pragma once
#include <vector>
using std::vector;

class DisjointSets {
public:
    vector<int> data;
    void addelements(int n);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);
};
