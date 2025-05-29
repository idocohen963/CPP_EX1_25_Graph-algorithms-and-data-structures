#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include <iostream>
#include <stdexcept>
#include "../include/Graph.hpp"
#include "../include/Algorithms.hpp"

using namespace graph;
using namespace std;

TEST_CASE("Graph construction and basic operations") {
    SUBCASE("Graph constructor with valid input") {
        Graph g(5);
        CHECK(g.getNumVertices() == 5);
    }
    
    SUBCASE("Graph constructor with invalid input") {
        CHECK_THROWS_AS(Graph(-1), std::invalid_argument);
        CHECK_THROWS_AS(Graph(0), std::invalid_argument);
    }
    
    SUBCASE("Adding and removing edges") {
        Graph g(5);
        
        // Add edges
        g.addEdge(0, 1, 5);
        g.addEdge(1, 2, 3);
        g.addEdge(2, 3, 1);
        
        // Check edges exist
        CHECK(g.hasEdge(0, 1));
        CHECK(g.hasEdge(1, 0)); // Undirected graph
        CHECK(g.hasEdge(1, 2));
        CHECK(g.hasEdge(2, 3));
        CHECK_FALSE(g.hasEdge(0, 2));
        
        // Remove edge
        g.removeEdge(1, 2);
        CHECK_FALSE(g.hasEdge(1, 2));
        CHECK_FALSE(g.hasEdge(2, 1));
        
        // Try to remove non-existent edge
        CHECK_THROWS_AS(g.removeEdge(0, 3), std::invalid_argument);
        
        // Try to add self-loop
        CHECK_THROWS_AS(g.addEdge(0, 0), std::invalid_argument);
        
        // Try to add duplicate edge
        CHECK_THROWS_AS(g.addEdge(0, 1), std::invalid_argument);
    }
    
    SUBCASE("Copy constructor and assignment operator") {
        Graph g1(4);
        g1.addEdge(0, 1, 2);
        g1.addEdge(1, 2, 3);
        g1.addEdge(2, 3, 4);
        
        // Test copy constructor
        Graph g2(g1);
        CHECK(g2.getNumVertices() == 4);
        CHECK(g2.hasEdge(0, 1));
        CHECK(g2.hasEdge(1, 2));
        CHECK(g2.hasEdge(2, 3));
        
        // Modify g1 and check that g2 is not affected
        g1.removeEdge(1, 2);
        CHECK(g1.hasEdge(0, 1));
        CHECK_FALSE(g1.hasEdge(1, 2));
        CHECK(g2.hasEdge(1, 2)); // g2 should still have this edge
        
        // Test assignment operator
        Graph g3(2);
        g3 = g2;
        CHECK(g3.getNumVertices() == 4);
        CHECK(g3.hasEdge(0, 1));
        CHECK(g3.hasEdge(1, 2));
        CHECK(g3.hasEdge(2, 3));
        
        // Self-assignment 
        g3 = g3;
        CHECK(g3.getNumVertices() == 4);
        CHECK(g3.hasEdge(0, 1));
    }
}

TEST_CASE("Graph algorithms") {
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    
    SUBCASE("BFS algorithm") {
        Graph bfsTree = Algorithms::bfs(g, 0);
        
        // BFS tree should have all vertices
        CHECK(bfsTree.getNumVertices() == 6);
        
        // Check some expected edges in the BFS tree
        CHECK(bfsTree.hasEdge(0, 1));
        CHECK(bfsTree.hasEdge(0, 2));
        // Either path is valid in BFS
        bool validPath = bfsTree.hasEdge(1, 3) || bfsTree.hasEdge(2, 3);
        CHECK(validPath);
        
        // Check invalid source vertex
        CHECK_THROWS_AS(Algorithms::bfs(g, -1), std::out_of_range);
        CHECK_THROWS_AS(Algorithms::bfs(g, 6), std::out_of_range);
    }
    
    SUBCASE("DFS algorithm") {
        Graph dfsTree = Algorithms::dfs(g, 0);
        
        // DFS tree should have all vertices
        CHECK(dfsTree.getNumVertices() == 6);
        
        // Check invalid source vertex
        CHECK_THROWS_AS(Algorithms::dfs(g, -1), std::out_of_range);
        CHECK_THROWS_AS(Algorithms::dfs(g, 6), std::out_of_range);
    }
    
    SUBCASE("Dijkstra algorithm") {
        Graph shortestPaths = Algorithms::dijkstra(g, 0);
        
        // Shortest paths tree should have all vertices
        CHECK(shortestPaths.getNumVertices() == 6);
        
        // Check invalid source vertex
        CHECK_THROWS_AS(Algorithms::dijkstra(g, -1), std::out_of_range);
        CHECK_THROWS_AS(Algorithms::dijkstra(g, 6), std::out_of_range);
        
        // Check graph with negative weights
        Graph g2(3);
        g2.addEdge(0, 1, -2); // Negative weight
        CHECK_THROWS_AS(Algorithms::dijkstra(g2, 0), std::invalid_argument);
    }
    
    SUBCASE("Prim algorithm") {
        Graph primMST = Algorithms::prim(g);
        
        // MST should have all vertices
        CHECK(primMST.getNumVertices() == 6);
        
        // MST should have n-1 edges for n vertices
        int edgeCount = 0;
        for (int i = 0; i < 6; ++i) {
            for (int j = i + 1; j < 6; ++j) {
                if (primMST.hasEdge(i, j)) {
                    edgeCount++;
                }
            }
        }
        CHECK(edgeCount == 5);
        
        // Check disconnected graph
        Graph g2(3);
        g2.addEdge(0, 1, 1); // Only connect vertices 0 and 1, leaving 2 disconnected
        CHECK_THROWS_AS(Algorithms::prim(g2), std::invalid_argument);
    }
    
    SUBCASE("Kruskal algorithm") {
        Graph kruskalMST = Algorithms::kruskal(g);
        
        // MST should have all vertices
        CHECK(kruskalMST.getNumVertices() == 6);
        
        // MST should have n-1 edges for n vertices
        int edgeCount = 0;
        for (int i = 0; i < 6; ++i) {
            for (int j = i + 1; j < 6; ++j) {
                if (kruskalMST.hasEdge(i, j)) {
                    edgeCount++;
                }
            }
        }
        CHECK(edgeCount == 5);
    }
}
