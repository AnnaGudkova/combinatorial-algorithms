#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "BipartiteGraph.hpp"

typedef std::pair<int,int> Point;

std::vector< Point > read_point_vector(std::ifstream &stream, const int &point_number) {
    std::vector< Point > point_vector;
    point_vector.resize(point_number);
    for (int i=0; i < point_number; i++) {
        int x, y;
        stream >> x >> y;
        point_vector[i] = (Point(x, y));
    }
    return point_vector;
}

inline float segment_length(const Point &point_from, const Point &point_to) {
    return sqrt(pow(point_from.first - point_to.first, 2) + 
                pow(point_from.second - point_to.second, 2)
               );
}

std::vector< int > calculateAccessiblePlaces(const std::vector<Point> &places, 
                                               const Point &point_from, 
                                               const Point &point_to) {
    std::vector< int > accesible_place;
    for (unsigned int i = 0; i < places.size(); i++) {
        float distance;
        distance = segment_length(places[i], point_from) + segment_length(places[i], point_to);

        if (distance <= 2*segment_length(point_from, point_to)) 
            accesible_place.push_back(i);
    }
    return accesible_place;
}

std::vector< std::vector<int> > createLinkList(const std::vector< Point > &way, const std::vector< Point > &places) {
    int partX_size = way.size() - 1;
    int partY_size = places.size();
    std::vector< std::vector<int> > link_list;
    link_list.resize(partX_size);
    for (int i=0; i < partX_size; i++) {
        link_list[i].resize(partY_size, 0);
        std::vector< int > accessible_place = calculateAccessiblePlaces(places, way[i], way[i+1]);
        for (unsigned int j=0; j < accessible_place.size(); j++) 
            link_list[i][accessible_place[j]] = 1;
    }
    return link_list;
}

int main(int argc, char** argv) {
    std::ifstream input_file;
    std::ofstream output_file;
    input_file.open("in.txt");
    output_file.open("out.txt");
    
    int point_number, place_number;
    input_file >> point_number >> place_number;

    std::vector< Point > bob_way;
    std::vector< Point > places;

    bob_way = read_point_vector(input_file, point_number);
    places  = read_point_vector(input_file, place_number);

    std::vector< std::vector<int> > link_list;
    link_list = createLinkList(bob_way, places);

    BipartiteGraph graph(link_list);
    std::vector<int> meeted_place = graph.getMaximumMatchingVector();

    int number_of_visited_place = 0;
    for (unsigned int i = 0; i < meeted_place.size(); i++)
        if (meeted_place[i] >= 0)
            number_of_visited_place++;

    output_file << number_of_visited_place + bob_way.size() << std::endl;

    return 0;
}
