// idocohen963@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#define private public
#include "../include/Graph.hpp"
#include "../include/Algorithms.hpp"
#undef private
#include "../include/Queue.hpp"
#include "../include/PriorityQueue.hpp"
#include "../include/UnionFind.hpp"
#include <stdexcept>
#include <iostream>

using namespace graph;

// Graph Tests
TEST_CASE("Graph Construction and Basic Operations") {
    SUBCASE("Graph Constructor") {
        Graph g(5);
        CHECK(g.getNumVertices() == 5);
        
        // Invalid number of vertices
        CHECK_THROWS_AS(Graph(-1), std::invalid_argument);
        CHECK_THROWS_AS(Graph(0), std::invalid_argument);
    }
    
    SUBCASE("Add Edges") {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(0, 2, 3);
        g.addEdge(1, 3, 5);
        g.addEdge(2, 4, 7);
        
        CHECK(g.hasEdge(0, 1));
        CHECK(g.hasEdge(1, 0)); // Undirected graph
        CHECK(g.hasEdge(0, 2));
        CHECK(g.hasEdge(1, 3));
        CHECK(g.hasEdge(2, 4));
        CHECK_FALSE(g.hasEdge(0, 3));
        CHECK_FALSE(g.hasEdge(1, 4));
        
        // Invalid vertices
        CHECK_THROWS_AS(g.addEdge(-1, 2), std::out_of_range);
        CHECK_THROWS_AS(g.addEdge(0, 5), std::out_of_range);
        CHECK_THROWS_AS(g.hasEdge(-1, 2), std::out_of_range);
        CHECK_THROWS_AS(g.hasEdge(0, 5), std::out_of_range);
        
        // Self-loops not allowed
        CHECK_THROWS_AS(g.addEdge(0, 0), std::invalid_argument);
        
        // Duplicate edges not allowed
        CHECK_THROWS_AS(g.addEdge(0, 1), std::invalid_argument);
    }
    
    SUBCASE("Remove Edges") {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        
        g.removeEdge(0, 1);
        CHECK_FALSE(g.hasEdge(0, 1));
        CHECK_FALSE(g.hasEdge(1, 0)); // Undirected graph
        
        // Edge does not exist
        CHECK_THROWS_AS(g.removeEdge(0, 3), std::invalid_argument);
        
        // Invalid vertices
        CHECK_THROWS_AS(g.removeEdge(-1, 2), std::out_of_range);
        CHECK_THROWS_AS(g.removeEdge(0, 5), std::out_of_range);
    }
    
    SUBCASE("Copy Constructor and Assignment Operator") {
        Graph g1(5);
        g1.addEdge(0, 1);
        g1.addEdge(0, 2);
        g1.addEdge(1, 3);
        g1.addEdge(2, 4);
        
        // Copy constructor
        Graph g2(g1);
        CHECK(g2.getNumVertices() == 5);
        CHECK(g2.hasEdge(0, 1));
        CHECK(g2.hasEdge(0, 2));
        CHECK(g2.hasEdge(1, 3));
        CHECK(g2.hasEdge(2, 4));
        
        // Assignment operator
        Graph g3(3);
        g3 = g1;
        CHECK(g3.getNumVertices() == 5);
        CHECK(g3.hasEdge(0, 1));
        CHECK(g3.hasEdge(0, 2));
        CHECK(g3.hasEdge(1, 3));
        CHECK(g3.hasEdge(2, 4));
        
        // Self-assignment
        g1 = g1;
        CHECK(g1.getNumVertices() == 5);
        CHECK(g1.hasEdge(0, 1));
        CHECK(g1.hasEdge(0, 2));
        CHECK(g1.hasEdge(1, 3));
        CHECK(g1.hasEdge(2, 4));
    }
    
    SUBCASE("Get Neighbors and Count") {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(0, 3);
        
        CHECK(g.getNumNeighbors(0) == 3);
        CHECK(g.getNumNeighbors(1) == 1);
        CHECK(g.getNumNeighbors(2) == 1);
        CHECK(g.getNumNeighbors(3) == 1);
        CHECK(g.getNumNeighbors(4) == 0);
        
        // Invalid vertex
        CHECK_THROWS_AS(g.getNumNeighbors(-1), std::out_of_range);
        CHECK_THROWS_AS(g.getNumNeighbors(5), std::out_of_range);
        CHECK_THROWS_AS(g.getNeighbors(-1), std::out_of_range);
        CHECK_THROWS_AS(g.getNeighbors(5), std::out_of_range);
    }
}

// Queue Tests
TEST_CASE("Queue Operations") {
    SUBCASE("Queue Constructor") {
        Queue q(5);
        CHECK(q.isEmpty());
        CHECK_FALSE(q.isFull());
        CHECK(q.getSize() == 0);
        
        // Invalid capacity
        CHECK_THROWS_AS(Queue(-1), std::invalid_argument);
        CHECK_THROWS_AS(Queue(0), std::invalid_argument);
    }
    
    SUBCASE("Enqueue and Dequeue") {
        Queue q(3);
        
        q.enqueue(10);
        CHECK_FALSE(q.isEmpty());
        CHECK_FALSE(q.isFull());
        CHECK(q.getSize() == 1);
        CHECK(q.peek() == 10);
        
        q.enqueue(20);
        q.enqueue(30);
        CHECK(q.isFull());
        CHECK(q.getSize() == 3);
        
        // Queue is full
        CHECK_THROWS_AS(q.enqueue(40), std::overflow_error);
        
        CHECK(q.dequeue() == 10);
        CHECK(q.dequeue() == 20);
        CHECK(q.dequeue() == 30);
        CHECK(q.isEmpty());
        
        // Queue is empty
        CHECK_THROWS_AS(q.dequeue(), std::underflow_error);
        CHECK_THROWS_AS(q.peek(), std::underflow_error);
    }
    
    SUBCASE("Circular Queue Behavior") {
        Queue q(3);
        
        q.enqueue(10);
        q.enqueue(20);
        q.enqueue(30);
        
        CHECK(q.dequeue() == 10);
        
        q.enqueue(40);
        CHECK(q.getSize() == 3);
        
        CHECK(q.dequeue() == 20);
        CHECK(q.dequeue() == 30);
        CHECK(q.dequeue() == 40);
        CHECK(q.isEmpty());
    }
}

// Priority Queue Tests
TEST_CASE("Priority Queue Operations") {
    SUBCASE("Priority Queue Constructor") {
        PriorityQueue pq(5);
        CHECK(pq.isEmpty());
        
        // Invalid capacity
        CHECK_THROWS_AS(PriorityQueue(-1), std::invalid_argument);
        CHECK_THROWS_AS(PriorityQueue(0), std::invalid_argument);
    }
    
    SUBCASE("Insert and Extract Min") {
        PriorityQueue pq(5);
        
        pq.insert(0, 10);
        CHECK_FALSE(pq.isEmpty());
        CHECK(pq.contains(0));
        
        pq.insert(1, 5);
        pq.insert(2, 15);
        pq.insert(3, 7);
        
        CHECK(pq.extractMin() == 1); // Priority 5
        CHECK(pq.extractMin() == 3); // Priority 7
        CHECK(pq.extractMin() == 0); // Priority 10
        CHECK(pq.extractMin() == 2); // Priority 15
        CHECK(pq.isEmpty());
        
        // Priority queue is empty
        CHECK_THROWS_AS(pq.extractMin(), std::underflow_error);
        
        // Invalid vertex
        CHECK_THROWS_AS(pq.insert(-1, 10), std::out_of_range);
        CHECK_THROWS_AS(pq.insert(5, 10), std::out_of_range);
        
        // Vertex already in queue
        pq.insert(0, 10);
        CHECK_THROWS_AS(pq.insert(0, 5), std::invalid_argument);
    }
    
    SUBCASE("Decrease Key") {
        PriorityQueue pq(5);
        
        pq.insert(0, 10);
        pq.insert(1, 20);
        pq.insert(2, 30);
        pq.insert(3, 40);
        
        pq.decreaseKey(2, 5);
        CHECK(pq.extractMin() == 2); // Priority decreased to 5
        
        // Invalid vertex
        CHECK_THROWS_AS(pq.decreaseKey(-1, 5), std::out_of_range);
        CHECK_THROWS_AS(pq.decreaseKey(5, 5), std::out_of_range);
        
        // Vertex not in queue
        CHECK_THROWS_AS(pq.decreaseKey(4, 5), std::invalid_argument);
        
        // Increase key (no effect)
        pq.decreaseKey(1, 25);
        CHECK(pq.extractMin() == 0); // Priority 10
    }
}

// Union-Find Tests
TEST_CASE("Union-Find Operations") {
    SUBCASE("Find") {
        UnionFind uf(5);
        
        // Initially, each element is its own representative
        CHECK(uf.find(0) == 0);
        CHECK(uf.find(1) == 1);
        CHECK(uf.find(2) == 2);
        CHECK(uf.find(3) == 3);
        CHECK(uf.find(4) == 4);
        
        // Invalid element
        CHECK_THROWS_AS(uf.find(-1), std::out_of_range);
        CHECK_THROWS_AS(uf.find(5), std::out_of_range);
    }
    
    SUBCASE("Union") {
        UnionFind uf(5);
        
        // Union 0 and 1
        CHECK(uf.unionSets(0, 1));
        CHECK(uf.find(0) == uf.find(1));
        
        // Union 2 and 3
        CHECK(uf.unionSets(2, 3));
        CHECK(uf.find(2) == uf.find(3));
        
        // Union 0 and 2 (merges two sets)
        CHECK(uf.unionSets(0, 2));
        CHECK(uf.find(0) == uf.find(2));
        CHECK(uf.find(1) == uf.find(3));
        
        // Elements already in the same set
        CHECK_FALSE(uf.unionSets(0, 1));
        CHECK_FALSE(uf.unionSets(2, 3));
        
        // Invalid elements
        CHECK_THROWS_AS(uf.unionSets(-1, 2), std::out_of_range);
        CHECK_THROWS_AS(uf.unionSets(0, 5), std::out_of_range);
    }
    
    SUBCASE("Path Compression") {
        UnionFind uf(5);
        
        // Create a chain: 0 -> 1 -> 2 -> 3 -> 4
        uf.unionSets(0, 1);
        uf.unionSets(1, 2);
        uf.unionSets(2, 3);
        uf.unionSets(3, 4);
        
        // Find should compress the path
        int root = uf.find(0);
        CHECK(uf.find(4) == root);
        
        // After path compression, all elements should point directly to the root
        CHECK(uf.find(1) == root);
        CHECK(uf.find(2) == root);
        CHECK(uf.find(3) == root);
    }
}

// BFS Algorithm Tests
TEST_CASE("BFS Algorithm") {
    SUBCASE("Basic BFS") {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        
        Graph bfsTree = Algorithms::bfs(g, 0);
        
        // BFS tree should have all vertices
        CHECK(bfsTree.getNumVertices() == 5);
        
        // Check BFS tree edges
        CHECK(bfsTree.hasEdge(0, 1));
        CHECK(bfsTree.hasEdge(0, 2));
        CHECK(bfsTree.hasEdge(1, 3));
        CHECK(bfsTree.hasEdge(2, 4));
        
        // These edges should not be in the BFS tree
        CHECK_FALSE(bfsTree.hasEdge(1, 2));
        CHECK_FALSE(bfsTree.hasEdge(0, 3));
        CHECK_FALSE(bfsTree.hasEdge(0, 4));
        CHECK_FALSE(bfsTree.hasEdge(1, 4));
        CHECK_FALSE(bfsTree.hasEdge(2, 3));
        CHECK_FALSE(bfsTree.hasEdge(3, 4));
    }
    
    SUBCASE("BFS with Different Source") {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        
        Graph bfsTree = Algorithms::bfs(g, 2);
        
        // Check BFS tree edges
        CHECK(bfsTree.hasEdge(2, 0));
        CHECK(bfsTree.hasEdge(2, 4));
        CHECK(bfsTree.hasEdge(0, 1));
        CHECK(bfsTree.hasEdge(1, 3));
        
        // Invalid source vertex
        CHECK_THROWS_AS(Algorithms::bfs(g, -1), std::out_of_range);
        CHECK_THROWS_AS(Algorithms::bfs(g, 5), std::out_of_range);
    }
    
    SUBCASE("BFS with Disconnected Graph") {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(2, 3);
        // Vertex 4 is isolated
        
        Graph bfsTree = Algorithms::bfs(g, 0);
        
        // Check BFS tree edges
        CHECK(bfsTree.hasEdge(0, 1));
        CHECK_FALSE(bfsTree.hasEdge(0, 2));
        CHECK_FALSE(bfsTree.hasEdge(0, 3));
        CHECK_FALSE(bfsTree.hasEdge(0, 4));
        CHECK_FALSE(bfsTree.hasEdge(1, 2));
        CHECK_FALSE(bfsTree.hasEdge(1, 3));
        CHECK_FALSE(bfsTree.hasEdge(1, 4));
    }
}

// DFS Algorithm Tests
TEST_CASE("DFS Algorithm") {
    SUBCASE("Basic DFS") {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        
        Graph dfsTree = Algorithms::dfs(g, 0);
        
        // DFS tree should have all vertices
        CHECK(dfsTree.getNumVertices() == 5);
        
        // Check that all vertices are reachable from source
        CHECK(dfsTree.hasEdge(0, 1));
        CHECK(dfsTree.hasEdge(0, 2));
        
        // Check that the tree is valid (no cycles)
        int edgeCount = 0;
        for (int i = 0; i < 5; i++) {
            const Graph::EdgeNode* neighbor = dfsTree.getNeighbors(i);
            while (neighbor != nullptr) {
                edgeCount++;
                neighbor = neighbor->next;
            }
        }
        CHECK(edgeCount / 2 == 4); // Undirected graph, so divide by 2
        
        // Invalid source vertex
        CHECK_THROWS_AS(Algorithms::dfs(g, -1), std::out_of_range);
        CHECK_THROWS_AS(Algorithms::dfs(g, 5), std::out_of_range);
    }
    
    SUBCASE("DFS with Different Source") {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(0, 2);
        g.addEdge(1, 3);
        g.addEdge(2, 4);
        
        Graph dfsTree = Algorithms::dfs(g, 2);
        
        // Check that all vertices are reachable from source
        CHECK(dfsTree.hasEdge(2, 0));
        CHECK(dfsTree.hasEdge(2, 4));
    }
    
    SUBCASE("DFS with Disconnected Graph") {
        Graph g(5);
        g.addEdge(0, 1);
        g.addEdge(2, 3);
        // Vertex 4 is isolated
        
        Graph dfsTree = Algorithms::dfs(g, 0);
        
        // Check DFS tree edges
        CHECK(dfsTree.hasEdge(0, 1));
        CHECK_FALSE(dfsTree.hasEdge(0, 2));
        CHECK_FALSE(dfsTree.hasEdge(0, 3));
        CHECK_FALSE(dfsTree.hasEdge(0, 4));
    }
}

// Dijkstra Algorithm Tests
TEST_CASE("Dijkstra Algorithm") {
    SUBCASE("Basic Dijkstra") {
        Graph g(5);
        g.addEdge(0, 1, 10);
        g.addEdge(0, 2, 5);
        g.addEdge(1, 3, 1);
        g.addEdge(2, 1, 3);
        g.addEdge(2, 3, 9);
        g.addEdge(2, 4, 2);
        g.addEdge(3, 4, 4);
        
        Graph shortestPathsTree = Algorithms::dijkstra(g, 0);
        
        // Check shortest paths tree edges and weights
        CHECK(shortestPathsTree.hasEdge(0, 2)); // 0 -> 2 (weight 5)
        CHECK(shortestPathsTree.hasEdge(2, 1)); // 2 -> 1 (weight 3)
        CHECK(shortestPathsTree.hasEdge(2, 4)); // 2 -> 4 (weight 2)
        CHECK(shortestPathsTree.hasEdge(1, 3)); // 1 -> 3 (weight 1)
        
        // Invalid source vertex
        CHECK_THROWS_AS(Algorithms::dijkstra(g, -1), std::out_of_range);
        CHECK_THROWS_AS(Algorithms::dijkstra(g, 5), std::out_of_range);
    }
    
    SUBCASE("Dijkstra with Negative Weights") {
        Graph g(3);
        g.addEdge(0, 1, 1);
        g.addEdge(1, 2, -1); // Negative weight
        
        // Dijkstra doesn't work with negative weights
        CHECK_THROWS_AS(Algorithms::dijkstra(g, 0), std::invalid_argument);
    }
    
    SUBCASE("Dijkstra with Disconnected Graph") {
        Graph g(5);
        g.addEdge(0, 1, 10);
        g.addEdge(2, 3, 5);
        // Vertex 4 is isolated
        
        Graph shortestPathsTree = Algorithms::dijkstra(g, 0);
        
        // Check shortest paths tree edges
        CHECK(shortestPathsTree.hasEdge(0, 1));
        CHECK_FALSE(shortestPathsTree.hasEdge(0, 2));
        CHECK_FALSE(shortestPathsTree.hasEdge(0, 3));
        CHECK_FALSE(shortestPathsTree.hasEdge(0, 4));
    }
}

// Prim Algorithm Tests
TEST_CASE("Prim Algorithm") {
    SUBCASE("Basic Prim") {
        Graph g(5);
        g.addEdge(0, 1, 2);
        g.addEdge(0, 3, 6);
        g.addEdge(1, 2, 3);
        g.addEdge(1, 3, 8);
        g.addEdge(1, 4, 5);
        g.addEdge(2, 4, 7);
        g.addEdge(3, 4, 9);
        
        Graph mst = Algorithms::prim(g);
        
        // MST should have all vertices
        CHECK(mst.getNumVertices() == 5);
        
        // MST should have n-1 edges
        int edgeCount = 0;
        for (int i = 0; i < 5; i++) {
            const Graph::EdgeNode* neighbor = mst.getNeighbors(i);
            while (neighbor != nullptr) {
                edgeCount++;
                neighbor = neighbor->next;
            }
        }
        CHECK(edgeCount / 2 == 4); // Undirected graph, so divide by 2
        
        // Check MST edges
        CHECK(mst.hasEdge(0, 1)); // Weight 2
        CHECK(mst.hasEdge(1, 2)); // Weight 3
        CHECK(mst.hasEdge(1, 4)); // Weight 5
        CHECK(mst.hasEdge(0, 3)); // Weight 6
        
        // These edges should not be in the MST
        CHECK_FALSE(mst.hasEdge(1, 3)); // Weight 8
        CHECK_FALSE(mst.hasEdge(2, 4)); // Weight 7
        CHECK_FALSE(mst.hasEdge(3, 4)); // Weight 9
    }
    
    SUBCASE("Prim with Disconnected Graph") {
        Graph g(5);
        g.addEdge(0, 1, 2);
        g.addEdge(2, 3, 3);
        // Vertex 4 is isolated
        
        // Prim requires a connected graph
        CHECK_THROWS_AS(Algorithms::prim(g), std::invalid_argument);
    }
}

// Kruskal Algorithm Tests
TEST_CASE("Kruskal Algorithm") {
    SUBCASE("Basic Kruskal") {
        Graph g(5);
        g.addEdge(0, 1, 2);
        g.addEdge(0, 3, 6);
        g.addEdge(1, 2, 3);
        g.addEdge(1, 3, 8);
        g.addEdge(1, 4, 5);
        g.addEdge(2, 4, 7);
        g.addEdge(3, 4, 9);
        
        Graph mst = Algorithms::kruskal(g);
        
        // MST should have all vertices
        CHECK(mst.getNumVertices() == 5);
        
        // MST should have n-1 edges
        int edgeCount = 0;
        for (int i = 0; i < 5; i++) {
            const Graph::EdgeNode* neighbor = mst.getNeighbors(i);
            while (neighbor != nullptr) {
                edgeCount++;
                neighbor = neighbor->next;
            }
        }
        CHECK(edgeCount / 2 == 4); // Undirected graph, so divide by 2
        
        // Check MST edges
        CHECK(mst.hasEdge(0, 1)); // Weight 2
        CHECK(mst.hasEdge(1, 2)); // Weight 3
        CHECK(mst.hasEdge(1, 4)); // Weight 5
        CHECK(mst.hasEdge(0, 3)); // Weight 6
        
        // These edges should not be in the MST
        CHECK_FALSE(mst.hasEdge(1, 3)); // Weight 8
        CHECK_FALSE(mst.hasEdge(2, 4)); // Weight 7
        CHECK_FALSE(mst.hasEdge(3, 4)); // Weight 9
    }
    
    SUBCASE("Kruskal with Disconnected Graph") {
        Graph g(5);
        g.addEdge(0, 1, 2);
        g.addEdge(2, 3, 3);
        // Vertex 4 is isolated
        
        Graph mst = Algorithms::kruskal(g);
        
        // MST should have all vertices
        CHECK(mst.getNumVertices() == 5);
        
        // MST should have fewer than n-1 edges for a disconnected graph
        int edgeCount = 0;
        for (int i = 0; i < 5; i++) {
            const Graph::EdgeNode* neighbor = mst.getNeighbors(i);
            while (neighbor != nullptr) {
                edgeCount++;
                neighbor = neighbor->next;
            }
        }
        CHECK(edgeCount / 2 == 2); // Undirected graph, so divide by 2
        
        // Check MST edges
        CHECK(mst.hasEdge(0, 1)); // Weight 2
        CHECK(mst.hasEdge(2, 3)); // Weight 3
    }
}

// Edge Cases and Stress Tests
TEST_CASE("Edge Cases and Stress Tests") {
    SUBCASE("Empty Graph") {
        // Empty graph 
       CHECK_THROWS_AS(Graph g(0), std::invalid_argument); // Cannot create a graph with 0 vertices
         
        // graph with 1 edges
        Graph g1(1);
        CHECK(Algorithms::isConnected(g1)); // Single vertex is connected
    }
    
    SUBCASE("Large Graph") {
        const int size = 100;
        Graph g(size);
        
        // Create a connected graph
        for (int i = 0; i < size - 1; i++) {
            g.addEdge(i, i + 1);
        }
        
        // Run algorithms on large graph
        Graph bfsTree = Algorithms::bfs(g, 0);
        Graph dfsTree = Algorithms::dfs(g, 0);
        Graph shortestPathsTree = Algorithms::dijkstra(g, 0);
        Graph mstPrim = Algorithms::prim(g);
        Graph mstKruskal = Algorithms::kruskal(g);
        
        // Check that all trees have the correct number of vertices
        CHECK(bfsTree.getNumVertices() == size);
        CHECK(dfsTree.getNumVertices() == size);
        CHECK(shortestPathsTree.getNumVertices() == size);
        CHECK(mstPrim.getNumVertices() == size);
        CHECK(mstKruskal.getNumVertices() == size);
    }
    
    SUBCASE("Cycle Detection") {
        Graph g(3);
        g.addEdge(0, 1);
        g.addEdge(1, 2);
        g.addEdge(2, 0);
        
        // BFS and DFS should not create cycles
        Graph bfsTree = Algorithms::bfs(g, 0);
        Graph dfsTree = Algorithms::dfs(g, 0);
        
        // Check that trees have n-1 edges
        int bfsEdgeCount = 0;
        int dfsEdgeCount = 0;
        
        for (int i = 0; i < 3; i++) {
            const Graph::EdgeNode* neighbor = bfsTree.getNeighbors(i);
            while (neighbor != nullptr) {
                bfsEdgeCount++;
                neighbor = neighbor->next;
            }
            
            neighbor = dfsTree.getNeighbors(i);
            while (neighbor != nullptr) {
                dfsEdgeCount++;
                neighbor = neighbor->next;
            }
        }
        
        CHECK(bfsEdgeCount / 2 == 2); // Undirected graph, so divide by 2
        CHECK(dfsEdgeCount / 2 == 2); // Undirected graph, so divide by 2
    }
}

// Main function
int main(int argc, char** argv) {
    doctest::Context context;
    context.applyCommandLine(argc, argv);
    
    int res = context.run();
    
    if (context.shouldExit()) {
        return res;
    }
    
    return res;
}
