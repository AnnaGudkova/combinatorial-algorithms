#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "TransportationNetwork.hpp"

class BipartiteGraph {
    private:
        int left_vertex_number;
        int rigth_vertex_number;
        std::vector< std::vector<int> > link_list;
        
    public:
        
        TransportationNetwork createTransportationNetwork();
        void loadFromTransportationNetwork(TransportationNetwork&);
        BipartiteGraph();
        BipartiteGraph(const int&, const int&);
        ~BipartiteGraph();
        BipartiteGraph getMaximumMatchingGraph();
        std::vector<int> getMaximumMatchingVector();
        friend std::ifstream& operator >> (std::ifstream&, BipartiteGraph&);
        friend std::ofstream& operator << (std::ofstream&, BipartiteGraph&);
};

