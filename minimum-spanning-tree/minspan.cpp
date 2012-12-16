#include <iostream>
#include <fstream>

#include "DisjointSetUnion.hpp"
#include "WeightedDirectedGraph.hpp"

int main(int argc, char **argv) {
    WeightedDirectedGraph graph;
    WeightedDirectedGraph minimum_spanning_tree;

    std::ifstream input_stream;
    std::ofstream output_stream;

    input_stream.open("in.txt");
    output_stream.open("out.txt");

    input_stream >> graph;

    minimum_spanning_tree = graph.getMinimumSpanningTree();

    output_stream << minimum_spanning_tree;

    input_stream.close();
    output_stream.close();

    return 0;
}
