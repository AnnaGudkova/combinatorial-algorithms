#include "WeightedDirectedGraph.hpp"

WeightedDirectedGraph::WeightedDirectedGraph() {}

WeightedDirectedGraph::~WeightedDirectedGraph() {}

std::vector< std::pair<int, std::pair<int, int> > > WeightedDirectedGraph::getEdgeVector() {
    std::set<std::pair< int, std::pair<int, int> > > edge_set;
    for (unsigned int vertex_counter=0; vertex_counter != this->adjacency_list.size(); vertex_counter++) {
        for (unsigned int child_counter=0; child_counter != this->adjacency_list[vertex_counter].size(); child_counter++) {
            int edge_child  = this->adjacency_list[vertex_counter][child_counter].first;
            int edge_weight = this->adjacency_list[vertex_counter][child_counter].second;
            std::pair< int, std::pair<int, int> > edge; 
            edge = std::make_pair(edge_weight, std::make_pair(edge_child, vertex_counter));
            if (edge_set.find(edge) == edge_set.end()) {
                std::swap(edge.second.first, edge.second.second);
                edge_set.insert(edge);
            }
        }
    }
    std::vector< std::pair<int, std::pair<int, int> > > edge_vector; 

    std::set<std::pair< int, std::pair<int, int> > >::iterator edge_set_iterator;
    for (edge_set_iterator = edge_set.begin(); edge_set_iterator != edge_set.end(); edge_set_iterator++) {
        edge_vector.push_back(*edge_set_iterator);
    }

    return edge_vector;
}

WeightedDirectedGraph WeightedDirectedGraph::graphFromEdges(std::vector< std::pair<int, std::pair<int, int> > > edge_vector) {
    WeightedDirectedGraph return_graph;
    return_graph.adjacency_list.resize(this->adjacency_list.size());

    for (unsigned int edge_counter=0; edge_counter < edge_vector.size(); edge_counter++) {
        int vertex_one = edge_vector[edge_counter].second.first;
        int vertex_two = edge_vector[edge_counter].second.second;

        std::pair<int,int> new_vertex;
        new_vertex.second = edge_vector[edge_counter].first;
        
        new_vertex.first = vertex_two;
        return_graph.adjacency_list[vertex_one].push_back(new_vertex);

        new_vertex.first = vertex_one;
        return_graph.adjacency_list[vertex_two].push_back(new_vertex);
    }
    for (unsigned int vertex_counter=0; vertex_counter < return_graph.adjacency_list.size(); vertex_counter++)
        std::sort(return_graph.adjacency_list[vertex_counter].begin(), return_graph.adjacency_list[vertex_counter].end());
    return return_graph;
}

WeightedDirectedGraph WeightedDirectedGraph::getMinimumSpanningTree() {
    std::vector< std::pair<int, std::pair<int, int> > > edge_vector; 
    edge_vector = this->getEdgeVector();
    DisjointSetUnion dsu;

    for (unsigned int vertex_counter=0; vertex_counter<this->adjacency_list.size(); vertex_counter++)
        dsu.makeSet(vertex_counter);
    
    std::vector< std::pair<int, std::pair<int, int> > > minimum_spanning_tree_edge_vector; 
    for (unsigned int edge_counter=0; edge_counter<edge_vector.size(); edge_counter++) {
        int set_one = dsu.findSet(edge_vector[edge_counter].second.first);
        int set_two = dsu.findSet(edge_vector[edge_counter].second.second);
        if (set_one != set_two) {
            dsu.unionSet(set_one, set_two);
            minimum_spanning_tree_edge_vector.push_back(edge_vector[edge_counter]);
        }
    }

    return this->graphFromEdges(minimum_spanning_tree_edge_vector);
}

std::ifstream& operator >> (std::ifstream& stream, WeightedDirectedGraph &graph) {
    int vertex_number;
    stream >> vertex_number;
    graph.adjacency_list.resize(vertex_number);
    for (int vertex_counter=0; vertex_counter<vertex_number; vertex_counter++) {
        std::pair<int,int> new_vertex;
        stream >> new_vertex.first;
        while (new_vertex.first != 0) {
            stream >> new_vertex.second;
            new_vertex.first--;
            graph.adjacency_list[vertex_counter].push_back(new_vertex);
            stream >> new_vertex.first;
        }
    }
    return stream;
}

std::ofstream& operator << (std::ofstream& stream, WeightedDirectedGraph &graph) {
    int weight = 0;
    for (unsigned int vertex_counter=0; vertex_counter != graph.adjacency_list.size(); vertex_counter++) {
        for (unsigned int child_counter=0; child_counter != graph.adjacency_list[vertex_counter].size(); child_counter++) {
            stream << graph.adjacency_list[vertex_counter][child_counter].first+1 << " "; 
            stream << graph.adjacency_list[vertex_counter][child_counter].second  << " ";
            weight += graph.adjacency_list[vertex_counter][child_counter].second;
        }
        stream << "0" << std::endl;
    }
    stream << weight / 2 << std::endl;
    return stream;
}
