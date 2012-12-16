headers = DisjointSetUnion WeightedDirectedGraph
program_name = minspan

source_names = $(addsuffix .cpp, $(headers))

build:
	g++ -g -Wall $(program_name).cpp $(source_names) -o $(program_name)
