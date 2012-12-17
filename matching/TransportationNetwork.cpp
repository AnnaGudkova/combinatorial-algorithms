#include "TransportationNetwork.hpp"

TransportationNetwork::TransportationNetwork() {}

TransportationNetwork::TransportationNetwork(const int &node_number) {
    this->capacity_adjacency_matrix.resize(node_number);
    for (int node_count=0; node_count < this->node_number(); node_count++)
        this->capacity_adjacency_matrix[node_count].resize(this->node_number(), 0);
    this->newFlow();
}

TransportationNetwork::TransportationNetwork(const std::vector< std::vector<int> > &capacity_adjacency_matrix) {
    this->capacity_adjacency_matrix = capacity_adjacency_matrix;
    this->newFlow();
}

TransportationNetwork::~TransportationNetwork() {}

std::vector< std::vector<int> > TransportationNetwork::getCapacityAdjacencyMatrix() {
    return this->capacity_adjacency_matrix;
}

void TransportationNetwork::setSource(const int &source) {
    this->source = source;
}

void TransportationNetwork::setSink(const int &sink) {
    this->sink = sink;
}

// Обнуление потока
void TransportationNetwork::newFlow() {
    this->arc_flow_matrix.resize(this->node_number());
    for (int node_count=0; node_count < this->node_number(); node_count++)
        this->arc_flow_matrix[node_count].resize(this->node_number(), 0);
}

inline int TransportationNetwork::node_number() {
    return this->capacity_adjacency_matrix.size();
}

// Поиск в глубину f-дополняющей (s,t) цепи
std::vector<int> TransportationNetwork::findComplementaryFlowPath() {
    std::vector<bool> marked_node;
    std::stack<int>   node_stack;
    std::vector<int>  flow_path;
    
    marked_node.resize(this->node_number(), false);
    
    node_stack.push(this->source);
    while (node_stack.size() != 0) {
        int node = node_stack.top();
        
        if (marked_node[node]) {
            node_stack.pop();
            flow_path.pop_back();
            continue;
        }
            
        marked_node[node] = true;
        flow_path.push_back(node);
        
        if (node == this->sink) {
            return flow_path;
        }
        
        for (int child_node=0; child_node < this->node_number(); child_node++) {
            int child_arc_capacity = this->capacity_adjacency_matrix[node][child_node];
            int child_arc_flow     = this->arc_flow_matrix[node][child_node];
            
            if (child_arc_capacity == 0) 
                continue;
            if (marked_node[child_node])
                continue;
                
            if (child_arc_capacity < 0 && child_arc_flow > 0) 
                node_stack.push(child_node);
            if (child_arc_capacity > 0 && child_arc_flow < child_arc_capacity)
                node_stack.push(child_node);
        }
    }
    
    return std::vector<int>();
}

// Значение потока, который можно пустить по ребру
int TransportationNetwork::getArcFlow(const int &node_from, const int &node_to) {
    int arc_capacity = this->capacity_adjacency_matrix[node_from][node_to];
    int arc_flow = this->arc_flow_matrix[node_from][node_to];
    
    if (arc_capacity < 0)
        return arc_flow;
    if (arc_capacity > 0)
        return arc_capacity - arc_flow;
        
    return 0;
}

// Определение величины потока, который можно пустить по дополняющей цепи
int TransportationNetwork::calculateFlowPathValue(std::vector<int> &flow_path) {
    int flow_path_value = 2000000;

    std::vector<int>::iterator node = flow_path.begin();
    for (node++; node != flow_path.end(); node++ ) {
        int arc_flow = this->getArcFlow(*(node-1), *node);
        if (arc_flow < flow_path_value)
            flow_path_value = arc_flow;
    }
    
    return flow_path_value;
}

// Обновление потока, идущего по ребру
void TransportationNetwork::upgradeArcFlow(const int &node_from, const int &node_to, const int &upgrade_value) {
    int arc_capacity = this->capacity_adjacency_matrix[node_from][node_to];
    if (arc_capacity < 0)
        this->arc_flow_matrix[node_from][node_to] -= upgrade_value;
    if (arc_capacity > 0) {
        this->arc_flow_matrix[node_from][node_to] += upgrade_value;
    }
}

// Обновление потока вдоль цепи.
void TransportationNetwork::upgradeNetworkFlow(std::vector<int> &flow_path) {
    int flow_path_value = this->calculateFlowPathValue(flow_path);
    
    std::vector<int>::iterator node = flow_path.begin();
    for (node++; node != flow_path.end(); node++ )
        this->upgradeArcFlow(*(node-1), *node, flow_path_value);
}

// Нахождение максимального потока сети. Алгоритм Форда-Фолкерсона.
TransportationNetwork TransportationNetwork::getMaximumFlow() {
    this->newFlow();

    std::vector<int> flow_path = this->findComplementaryFlowPath();
    for (; flow_path.size() != 0; flow_path = this->findComplementaryFlowPath())
        this->upgradeNetworkFlow(flow_path);
    
    return this->getNetworkFromFlow();
}

// Обход графа поиском в ширину, и возврат нового, состоящего только из ребер, 
//по которым идет поток
TransportationNetwork TransportationNetwork::getNetworkFromFlow() {
    std::vector<bool> marked_node;
    std::queue<int>   node_queue;
    
    TransportationNetwork new_network(this->node_number());
    
    marked_node.resize(this->node_number(), false);
    
    node_queue.push(this->source);
    marked_node[this->source] = true;
    while (node_queue.size() != 0) {
        int node = node_queue.front ();
        node_queue.pop();
        
        for (int child_node=0; child_node < this->node_number(); child_node++) {
            int child_arc_capacity = this->capacity_adjacency_matrix[node][child_node];
            int child_arc_flow     = this->arc_flow_matrix[node][child_node];
            
            if (child_arc_capacity == 0) 
                continue;
                
            if (child_arc_flow > 0) {
                new_network.capacity_adjacency_matrix[node][child_node] =  child_arc_flow;
                new_network.capacity_adjacency_matrix[child_node][node] = -child_arc_flow;
                if (marked_node[child_node])
                    continue;
                node_queue.push(child_node);
                marked_node[child_node] = true;
            }
        }
    }
    return new_network;
}

std::ofstream& operator << (std::ofstream &stream, TransportationNetwork &network) {
    for (int node=0; node < network.node_number(); node++) {
        for (int child_node=0; child_node < network.node_number(); child_node++)
            stream << network.capacity_adjacency_matrix[node][child_node] << " ";
        stream << std::endl;
    }
    
    return stream;
}

std::ifstream& operator >> (std::ifstream &stream, TransportationNetwork &network) {
    int node_number;
    stream >> node_number;
    stream >> network.source;
    stream >> network.sink;
    network.capacity_adjacency_matrix.resize(node_number);
    for (int node=0; node < network.node_number(); node++) {
        for (int child_node=0; child_node < network.node_number(); child_node++) {
            int child_capacity;
            stream >> child_capacity;
            network.capacity_adjacency_matrix[node].push_back(child_capacity);
        }
    }
    
    return stream;
}

