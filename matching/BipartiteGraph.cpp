#include "BipartiteGraph.hpp"

BipartiteGraph::BipartiteGraph() {}

BipartiteGraph::BipartiteGraph(const int &left_vertex_number, const int &rigth_vertex_number) {
    this->left_vertex_number  = left_vertex_number;
    this->rigth_vertex_number = rigth_vertex_number;
    this->link_list.resize(left_vertex_number);
    for (int left_vertex_count=0; left_vertex_count < left_vertex_number; left_vertex_count++)
        this->link_list[left_vertex_count].resize(rigth_vertex_number, 0);
}

BipartiteGraph::~BipartiteGraph() {}

TransportationNetwork BipartiteGraph::createTransportationNetwork() {
    std::vector< std::vector<int> > capacity_adjacency_matrix;
    
    int vertex_number = 1 + this->left_vertex_number + this->rigth_vertex_number + 1;
    
    capacity_adjacency_matrix.resize(vertex_number);
    for (int vertex_count=0; vertex_count < vertex_number; vertex_count++)
        capacity_adjacency_matrix[vertex_count].resize(vertex_number, 0);
        
    for (int left_vertex_count=0; left_vertex_count < this->left_vertex_number; left_vertex_count++) {
        capacity_adjacency_matrix[0][1+left_vertex_count] =  1;
        capacity_adjacency_matrix[1+left_vertex_count][0] = -1;
        
        for (int rigth_vertex_count=0; rigth_vertex_count < this->rigth_vertex_number; rigth_vertex_count++) 
            if (this->link_list[left_vertex_count][rigth_vertex_count]) {
                capacity_adjacency_matrix[1+left_vertex_count][1+this->left_vertex_number+rigth_vertex_count]  =  1;
                capacity_adjacency_matrix[1+this->left_vertex_number+rigth_vertex_count][1+left_vertex_count] = -1;
            }
    }
    
    for (int rigth_vertex_count=0; rigth_vertex_count < this->rigth_vertex_number; rigth_vertex_count++) {
        capacity_adjacency_matrix[1+this->left_vertex_number+rigth_vertex_count][vertex_number-1] =  1;
        capacity_adjacency_matrix[vertex_number-1][1+this->left_vertex_number+rigth_vertex_count] = -1;
    }
    
    TransportationNetwork network(capacity_adjacency_matrix);
    network.setSource(0);
    network.setSink(vertex_number-1);
    
    return network;
}

void BipartiteGraph::loadFromTransportationNetwork(TransportationNetwork &network) {
    std::vector< std::vector<int> > capacity_adjacency_matrix = network.getCapacityAdjacencyMatrix();
    for (int left_vertex_count=0; left_vertex_count < this->left_vertex_number; left_vertex_count++) 
        for (int rigth_vertex_count=0; rigth_vertex_count < this->rigth_vertex_number; rigth_vertex_count++) {
            int vertex_link;
            vertex_link = capacity_adjacency_matrix[1+left_vertex_count][1+this->left_vertex_number+rigth_vertex_count];
            this->link_list[left_vertex_count][rigth_vertex_count] = vertex_link % 2;
        }
}

BipartiteGraph BipartiteGraph::getMaximumMatchingGraph() {
    TransportationNetwork network = this->createTransportationNetwork();
    network = network.getMaximumFlow();
    BipartiteGraph graph(this->left_vertex_number, this->rigth_vertex_number);
    graph.loadFromTransportationNetwork(network);
    return graph;
}

std::vector<int> BipartiteGraph::getMaximumMatchingVector() {
    std::vector<int> matching_vector(this->left_vertex_number);
    BipartiteGraph graph = this->getMaximumMatchingGraph();
    for (int left_vertex_count=0; left_vertex_count < this->left_vertex_number; left_vertex_count++) 
        for (int rigth_vertex_count=0; rigth_vertex_count < this->rigth_vertex_number; rigth_vertex_count++)
            if (graph.link_list[left_vertex_count][rigth_vertex_count])
                matching_vector[left_vertex_count] = rigth_vertex_count;
    return matching_vector;
}

std::ifstream& operator >> (std::ifstream& stream, BipartiteGraph& graph) {
    int left_vertex_number;
    int rigth_vertex_number;
    stream >> left_vertex_number;
    stream >> rigth_vertex_number;
    graph.left_vertex_number  = left_vertex_number;
    graph.rigth_vertex_number = rigth_vertex_number;
    graph.link_list.resize(left_vertex_number);
    for (int left_vertex_count=0; left_vertex_count < left_vertex_number; left_vertex_count++)
        for (int rigth_vertex_count=0; rigth_vertex_count < rigth_vertex_number; rigth_vertex_count++) {
            int vertex_link;
            stream >> vertex_link;
            graph.link_list[left_vertex_count].push_back(vertex_link);
        }
    return stream;
}

std::ofstream& operator << (std::ofstream& stream, BipartiteGraph& graph) {
    stream << graph.left_vertex_number << " " ;
    stream << graph.rigth_vertex_number << std::endl ;
    for (int left_vertex_count=0; left_vertex_count < graph.left_vertex_number; left_vertex_count++) {
        for (int rigth_vertex_count=0; rigth_vertex_count < graph.rigth_vertex_number; rigth_vertex_count++) {
            stream << graph.link_list[left_vertex_count][rigth_vertex_count] << " ";
        }
        stream << std::endl;
    }
    return stream;       
}
