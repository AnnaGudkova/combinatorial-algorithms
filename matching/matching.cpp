#include <iostream>
#include <fstream>
#include <vector>

#include "BipartiteGraph.hpp"

int main(int argc, char **argv) {
    std::ifstream input_stream;
    std::ofstream output_stream;
    
    input_stream.open("in.txt");
    output_stream.open("out.txt");
    
    BipartiteGraph graph;
    
    input_stream  >> graph;
    
    std::vector<int> matching_vector;
    matching_vector = graph.getMaximumMatchingVector();
    
    for (unsigned int left_vertex_count=0; left_vertex_count < matching_vector.size(); left_vertex_count++)
        output_stream << matching_vector[left_vertex_count] + 1 << " ";
    
    return 0;
}
