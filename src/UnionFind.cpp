#include "../include/UnionFind.hpp"
#include <stdexcept>

namespace graph {

UnionFind::UnionFind(int size) : size(size) {
    parent = new int[size];
    rank = new int[size];
    
    // Initialize: each element is its own parent with rank 0
    for (int i = 0; i < size; ++i) {
        parent[i] = i;
        rank[i] = 0;
    }
}

UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

int UnionFind::find(int x) {
    if (x < 0 || x >= size) {
        throw std::out_of_range("Element index out of range");
    }
    
    // Path compression: make every examined node point directly to the root
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

bool UnionFind::unionSets(int x, int y) {
    if (x < 0 || x >= size || y < 0 || y >= size) {
        throw std::out_of_range("Element index out of range");
    }
    
    int rootX = find(x);
    int rootY = find(y);
    
    // Already in the same set
    if (rootX == rootY) {
        return false;
    }
    
    // Union by rank: attach smaller rank tree under root of higher rank tree
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        // If ranks are same, make one as root and increment its rank
        parent[rootY] = rootX;
        rank[rootX]++;
    }
    
    return true;
}

} // namespace graph
