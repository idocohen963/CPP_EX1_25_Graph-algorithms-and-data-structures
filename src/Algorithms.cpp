#include "../include/Algorithms.hpp"
#include "../include/Queue.hpp"
#include "../include/PriorityQueue.hpp"
#include "../include/UnionFind.hpp"
#include <stdexcept>

namespace graph {

Graph Algorithms::bfs(const Graph& g, int source) {
    int numVertices = g.getNumVertices();
    
    // Validate source vertex
    if (source < 0 || source >= numVertices) {
        throw std::out_of_range("Source vertex out of range");
    }
    
    // Create a new graph for the BFS tree
    Graph bfsTree(numVertices);
    
    // Initialize visited array and parent array
    bool* visited = new bool[numVertices];
    int* parent = new int[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        parent[i] = -1;  // -1 indicates no parent
    }
    
    // Create a queue for BFS
    Queue queue(numVertices);
    
    // Mark the source vertex as visited and enqueue it
    visited[source] = true;
    queue.enqueue(source);
    
    // BFS loop
    while (!queue.isEmpty()) {
        int u = queue.dequeue();
        
        // Get all adjacent vertices of the dequeued vertex u
        const Graph::EdgeNode* neighbor = g.getNeighbors(u);
        
        while (neighbor != nullptr) {
            int v = neighbor->dest;
            
            // If this adjacent vertex is not visited yet, mark it visited,
            // set its parent, and enqueue it
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                queue.enqueue(v);
            }
            
            neighbor = neighbor->next;
        }
    }
    
    // Build the BFS tree using the parent array
    for (int i = 0; i < numVertices; i++) {
        if (parent[i] != -1) {
            bfsTree.addEdge(parent[i], i);
        }
    }
    
    // Clean up
    delete[] visited;
    delete[] parent;
    
    return bfsTree;
}

void Algorithms::dfsVisit(const Graph& g, int vertex, bool* visited, int* parent, Graph& dfsTree) {
    visited[vertex] = true;
    
    // Visit all the adjacent vertices
    const Graph::EdgeNode* neighbor = g.getNeighbors(vertex);
    
    while (neighbor != nullptr) {
        int u = neighbor->dest;
        
        if (!visited[u]) {
            parent[u] = vertex;
            dfsTree.addEdge(vertex, u);
            dfsVisit(g, u, visited, parent, dfsTree);
        }
        
        neighbor = neighbor->next;
    }
}

Graph Algorithms::dfs(const Graph& g, int source) {
    int numVertices = g.getNumVertices();
    
    // Validate source vertex
    if (source < 0 || source >= numVertices) {
        throw std::out_of_range("Source vertex out of range");
    }
    
    // Create a new graph for the DFS tree
    Graph dfsTree(numVertices);
    
    // Initialize visited array and parent array
    bool* visited = new bool[numVertices];
    int* parent = new int[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
        parent[i] = -1;  // -1 indicates no parent
    }
    
    // Start DFS from the source vertex
    dfsVisit(g, source, visited, parent, dfsTree);
    
    // Clean up
    delete[] visited;
    delete[] parent;
    
    return dfsTree;
}

bool Algorithms::hasNegativeWeights(const Graph& g) {
    int numVertices = g.getNumVertices();
    
    for (int i = 0; i < numVertices; i++) {
        const Graph::EdgeNode* neighbor = g.getNeighbors(i);
        
        while (neighbor != nullptr) {
            if (neighbor->weight < 0) {
                return true;
            }
            neighbor = neighbor->next;
        }
    }
    
    return false;
}
const int INT_MAX = 2147483647;

Graph Algorithms::dijkstra(const Graph& g, int source) {
    int numVertices = g.getNumVertices();
    
    // Validate source vertex
    if (source < 0 || source >= numVertices) {
        throw std::out_of_range("Source vertex out of range");
    }
    
    // Check for negative weights
    if (hasNegativeWeights(g)) {
        throw std::invalid_argument("Graph contains negative weights");
    }
    
    // Create a new graph for the shortest paths tree
    Graph shortestPathsTree(numVertices);
    
    // Initialize distance array and parent array
    int* distance = new int[numVertices];
    int* parent = new int[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        distance[i] = INT_MAX;
        parent[i] = -1;  // -1 indicates no parent
    }
    
    // Distance from source to itself is 0
    distance[source] = 0;
    
    // Create a priority queue
    PriorityQueue pq(numVertices);
    
    // Add source to priority queue
    pq.insert(source, 0);
    
    // Process vertices in order of increasing distance
    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        
        // Get all adjacent vertices of u
        const Graph::EdgeNode* neighbor = g.getNeighbors(u);
        
        while (neighbor != nullptr) {
            int v = neighbor->dest;
            int weight = neighbor->weight;
            
            // If there is a shorter path to v through u
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                // Update distance of v
                distance[v] = distance[u] + weight;
                parent[v] = u;
                
                // Update priority queue
                if (pq.contains(v)) {
                    pq.decreaseKey(v, distance[v]);
                } else {
                    pq.insert(v, distance[v]);
                }
            }
            
            neighbor = neighbor->next;
        }
    }
    
    // Build the shortest paths tree using the parent array
    for (int i = 0; i < numVertices; i++) {
        if (parent[i] != -1) {
            shortestPathsTree.addEdge(parent[i], i, distance[i] - distance[parent[i]]);
        }
    }
    
    // Clean up
    delete[] distance;
    delete[] parent;
    
    return shortestPathsTree;
}

bool Algorithms::isConnected(const Graph& g) {
    int numVertices = g.getNumVertices();
    
    if (numVertices == 0) {
        return true;  // Empty graph is connected by definition
    }
    
    // Use a minimal BFS traversal to check if all vertices are reachable from vertex 0
    bool* visited = new bool[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        visited[i] = false;
    }
    
    // Start BFS from vertex 0
    Queue queue(numVertices);
    visited[0] = true;
    queue.enqueue(0);
    
    int visitedCount = 1;  // Vertex 0 is already visited
    
    while (!queue.isEmpty()) {
        int u = queue.dequeue();
        
        const Graph::EdgeNode* neighbor = g.getNeighbors(u);
        
        while (neighbor != nullptr) {
            int v = neighbor->dest;
            
            if (!visited[v]) {
                visited[v] = true;
                queue.enqueue(v);
                visitedCount++;
            }
            
            neighbor = neighbor->next;
        }
    }
    
    bool connected = (visitedCount == numVertices);
    
    // Clean up
    delete[] visited;
    
    return connected;
}

Graph Algorithms::prim(const Graph& g) {
    int numVertices = g.getNumVertices();
    
    // Check if graph is connected
    if (!isConnected(g)) {
        throw std::invalid_argument("Graph is not connected");
    }
    
    // Create a new graph for the MST
    Graph mst(numVertices);
    
    // Initialize key values and parent array
    int* key = new int[numVertices];
    int* parent = new int[numVertices];
    
    for (int i = 0; i < numVertices; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;  // -1 indicates no parent
    }
    
    // Start with vertex 0
    key[0] = 0;
    
    // Create a priority queue
    PriorityQueue pq(numVertices);
    
    // Add all vertices to priority queue
    for (int i = 0; i < numVertices; i++) {
        pq.insert(i, key[i]);
    }
    
    // Process vertices in order of increasing key value
    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        
        // Get all adjacent vertices of u
        const Graph::EdgeNode* neighbor = g.getNeighbors(u);
        
        while (neighbor != nullptr) {
            int v = neighbor->dest;
            int weight = neighbor->weight;
            
            // If v is in priority queue and weight of (u,v) is less than key of v
            if (pq.contains(v) && weight < key[v]) {
                // Update key of v
                key[v] = weight;
                parent[v] = u;
                
                // Update priority queue
                pq.decreaseKey(v, key[v]);
            }
            
            neighbor = neighbor->next;
        }
    }
    
    // Build the MST using the parent array
    for (int i = 1; i < numVertices; i++) {  // Start from 1 because vertex 0 has no parent
        if (parent[i] != -1) {
            mst.addEdge(parent[i], i, key[i]);
        }
    }
    
    // Clean up
    delete[] key;
    delete[] parent;
    
    return mst;
}

void Algorithms::SortEdges(Edge* edges, int edgeCount) {
    for (int i = 0; i < edgeCount - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < edgeCount; j++) {
            if (edges[j] < edges[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            Edge temp = edges[i];
            edges[i] = edges[minIdx];
            edges[minIdx] = temp;
        }
    }
}

Graph Algorithms::kruskal(const Graph& g) {
    int numVertices = g.getNumVertices();
    
    // Create a new graph for the MST
    Graph mst(numVertices);
    
    // Create an array of all edges in the graph
    int maxEdges = numVertices * (numVertices - 1) / 2;  // Maximum possible edges in an undirected graph
    Edge* edges = new Edge[maxEdges];
    int edgeCount = 0;
    
    // Collect all edges
    for (int i = 0; i < numVertices; i++) {
        const Graph::EdgeNode* neighbor = g.getNeighbors(i);
        
        while (neighbor != nullptr) {
            // Add edge only once (when i < neighbor->dest)
            if (i < neighbor->dest) {
                edges[edgeCount].src = i;
                edges[edgeCount].dest = neighbor->dest;
                edges[edgeCount].weight = neighbor->weight;
                edgeCount++;
            }
            
            neighbor = neighbor->next;
        }
    }
    
    // Sort edges by weight
    SortEdges(edges, edgeCount);
    
    // Create a Union-Find data structure
    UnionFind uf(numVertices);
    
    // Process edges in order of increasing weight
    for (int i = 0; i < edgeCount; i++) {
        int src = edges[i].src;
        int dest = edges[i].dest;
        
        // If including this edge does not cause a cycle
        if (uf.find(src) != uf.find(dest)) {
            // Include this edge in MST
            mst.addEdge(src, dest, edges[i].weight);
            
            // Union the sets
            uf.unionSets(src, dest);
        }
    }
    
    // Clean up
    delete[] edges;
    
    return mst;
}

} // namespace graph
