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
        void loadFromTransportationNetwork(TransportationNetwork&);
        TransportationNetwork createTransportationNetwork();
        
    public:
        BipartiteGraph();
        BipartiteGraph(const int&, const int&);
        BipartiteGraph(const std::vector< std::vector<int> >&);
        ~BipartiteGraph();

        BipartiteGraph getMaximumMatchingGraph();
        std::vector<int> getMaximumMatchingVector();
        std::vector< std::vector<int> > getLinkList();
        friend std::ifstream& operator >> (std::ifstream&, BipartiteGraph&);
        friend std::ofstream& operator << (std::ofstream&, BipartiteGraph&);
};

