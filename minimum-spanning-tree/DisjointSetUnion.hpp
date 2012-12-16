#pragma once

#include <vector>

class DisjointSetUnion {
    private:
        std::vector<int> parent;
    public:
        DisjointSetUnion();
        ~DisjointSetUnion();
        void makeSet(int);
        void unionSet(int, int);
        int  findSet(int);
};

