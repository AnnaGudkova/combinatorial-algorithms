#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

#include "DisjointSetUnion.hpp"

class WeightedGraph {
    private:
        std::vector< std::vector< std::pair<int, int> > > adjacency_list;
        std::vector< std::pair<int, std::pair<int, int> > > getEdgeVector();
        WeightedGraph graphFromEdges(std::vector< std::pair<int, std::pair<int, int> > >); 

    public:
        WeightedGraph();
        ~WeightedGraph();

        WeightedGraph getMinimumSpanningTree();

        friend std::ifstream& operator >> (std::ifstream&, WeightedGraph&);
        friend std::ofstream& operator << (std::ofstream&, WeightedGraph&);

};
