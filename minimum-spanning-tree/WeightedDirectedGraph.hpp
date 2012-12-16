#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

#include "DisjointSetUnion.hpp"

class WeightedDirectedGraph {
    private:
        std::vector< std::vector< std::pair<int, int> > > adjacency_list;
        std::vector< std::pair<int, std::pair<int, int> > > getEdgeVector();
        WeightedDirectedGraph graphFromEdges(std::vector< std::pair<int, std::pair<int, int> > >); 

    public:
        WeightedDirectedGraph();
        ~WeightedDirectedGraph();

        WeightedDirectedGraph getMinimumSpanningTree();

        friend std::ifstream& operator >> (std::ifstream&, WeightedDirectedGraph&);
        friend std::ofstream& operator << (std::ofstream&, WeightedDirectedGraph&);
};
