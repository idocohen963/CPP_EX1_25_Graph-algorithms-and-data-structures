// idocohen963@gmail.com
#include "../include/Graph.hpp"
#include <stdexcept>

namespace graph {

void Graph::validateVertex(int v) const {
    if (v < 0 || v >= numVertices) {
        throw std::out_of_range("Vertex index out of range: " + std::to_string(v));
    }
}

Graph::Graph(int numVertices) : numVertices(numVertices) {
    if (numVertices <= 0) {
        throw std::invalid_argument("Number of vertices must be positive");
    }
    
    adjList = new EdgeNode*[numVertices];
    for (int i = 0; i < numVertices; i++) {
        adjList[i] = nullptr;
    }
}

Graph::Graph(const Graph& other) : numVertices(other.numVertices) {
    // Allocate new adjacency list
    adjList = new EdgeNode*[numVertices];
    
    // Deep copy each adjacency list
    for (int i = 0; i < numVertices; i++) {
        adjList[i] = nullptr;
        const EdgeNode* current = other.adjList[i];
        EdgeNode** tail = &adjList[i];
        
        while (current != nullptr) {
            *tail = new EdgeNode(current->dest, current->weight);
            tail = &((*tail)->next);
            current = current->next;
        }
    }
}

Graph& Graph::operator=(const Graph& other) {
    if (this == &other) {
        return *this; // Self-assignment check
    }
    
    // Free existing resources
    for (int i = 0; i < numVertices; i++) {
        EdgeNode* current = adjList[i];
        while (current != nullptr) {
            EdgeNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjList;
    
    // Copy from other
    numVertices = other.numVertices;
    adjList = new EdgeNode*[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        adjList[i] = nullptr;
        const EdgeNode* current = other.adjList[i];
        EdgeNode** tail = &adjList[i];
        
        while (current != nullptr) {
            *tail = new EdgeNode(current->dest, current->weight);
            tail = &((*tail)->next);
            current = current->next;
        }
    }
    
    return *this;
}

Graph::~Graph() {
    for (int i = 0; i < numVertices; i++) {
        EdgeNode* current = adjList[i];
        while (current != nullptr) {
            EdgeNode* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] adjList;
}

bool Graph::hasEdge(int src, int dest) const {
    validateVertex(src);
    validateVertex(dest);
    
    EdgeNode* current = adjList[src];
    while (current != nullptr) {
        if (current->dest == dest) {
            return true;
        }
        current = current->next;
    }
    return false;
}

void Graph::addEdge(int src, int dest, int weight) {
    validateVertex(src);
    validateVertex(dest);
    
    // Prevent self-loops
    if (src == dest) {
        throw std::invalid_argument("Self-loops are not allowed");
    }
    
    // Check if edge already exists
    if (hasEdge(src, dest)) {
        throw std::invalid_argument("Edge already exists");
    }
    
    // Add edge from src to dest
    adjList[src] = new EdgeNode(dest, weight, adjList[src]);
    
    // Add edge from dest to src (undirected graph)
    adjList[dest] = new EdgeNode(src, weight, adjList[dest]);
}

void Graph::removeEdge(int src, int dest) {
    validateVertex(src);
    validateVertex(dest);
    
    // Check if edge exists
    if (!hasEdge(src, dest)) {
        throw std::invalid_argument("Edge does not exist");
    }
    
    // Remove edge from src to dest
    EdgeNode** current = &adjList[src];
    while (*current != nullptr && (*current)->dest != dest) {
        current = &((*current)->next);
    }
    
    if (*current != nullptr) {
        EdgeNode* temp = *current;
        *current = temp->next;
        delete temp;
    }
    
    // Remove edge from dest to src
    current = &adjList[dest];
    while (*current != nullptr && (*current)->dest != src) {
        current = &((*current)->next);
    }
    
    if (*current != nullptr) {
        EdgeNode* temp = *current;
        *current = temp->next;
        delete temp;
    }
} 

void Graph::print_graph() const {
    for (int i = 0; i < numVertices; i++) {
        std::cout << "Vertex " << i << " -> ";
        EdgeNode* current = adjList[i];
        
        while (current != nullptr) {
            std::cout << "(" << current->dest << ", weight: " << current->weight << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

int Graph::getNumVertices() const {
    return numVertices;
}

const Graph::EdgeNode* Graph::getNeighbors(int v) const {
    validateVertex(v);
    return adjList[v];
}

int Graph::getNumNeighbors(int v) const {
    validateVertex(v);
    
    int count = 0;
    EdgeNode* current = adjList[v];
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

} // namespace graph
