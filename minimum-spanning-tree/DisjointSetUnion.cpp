#include "DisjointSetUnion.hpp"

#define START_PARENT_NUMBER 10

DisjointSetUnion::DisjointSetUnion() {
    this->parent.resize(START_PARENT_NUMBER, -1);
}

DisjointSetUnion::~DisjointSetUnion() {}

void DisjointSetUnion::makeSet(int vertex) {
    while ((unsigned int) vertex >= this->parent.size())
        this->parent.resize(2 * this->parent.size(), -1);
    this->parent[vertex] = vertex;
}

void DisjointSetUnion::unionSet(int vertex_one, int vertex_two) {
    vertex_one = this->findSet(vertex_one);
    vertex_two = this->findSet(vertex_two);

    if (vertex_one != vertex_two) {
        this->parent[vertex_one] = vertex_two;
    }
}

// Применена эвристика сжатия пути
int  DisjointSetUnion::findSet(int vertex) {
    if (this->parent[vertex] == -1)
        return -1;
    if (this->parent[vertex] == vertex)
        return vertex;
    return this->parent[vertex] = this->findSet( this->parent[vertex] );
}

