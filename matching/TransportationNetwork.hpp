#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

class TransportationNetwork {
    private:
        int source;
        int sink;
        std::vector< std::vector<int> > capacity_adjacency_matrix;
        std::vector< std::vector<int> > arc_flow_matrix;
    
        void newFlow();    
        std::vector<int> findComplementaryFlowPath();
        int getArcFlow(const int&, const int&);
        int calculateFlowPathValue(std::vector<int>&);
        void upgradeArcFlow(const int &node_from, const int&, const int&);
        void upgradeNetworkFlow(std::vector<int>&);
        TransportationNetwork getNetworkFromFlow();

    public:
        TransportationNetwork();
        TransportationNetwork(const int&);
        TransportationNetwork(const std::vector< std::vector<int> >&);
        ~TransportationNetwork();
        int node_number();
        void setSource(const int&);
        void setSink(const int&);
        TransportationNetwork getMaximumFlow();
        std::vector< std::vector<int> > getCapacityAdjacencyMatrix();
        friend std::ifstream& operator >> (std::ifstream&, TransportationNetwork&);
        friend std::ofstream& operator << (std::ofstream&, TransportationNetwork&);
};

