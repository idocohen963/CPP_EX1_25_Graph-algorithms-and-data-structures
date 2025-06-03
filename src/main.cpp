// idocohen963@gmail.com
#include <iostream>
#include "../include/Graph.hpp"
#include "../include/Algorithms.hpp"

using namespace graph;
using namespace std;

int main() {
    // Create example graph
    cout << "Creating an example graph with 6 vertices" << endl;
    Graph g(6);
    
    // Add edges
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    
    // Print the graph
    cout << "\nOriginal graph:" << endl;
    g.print_graph();
    
    // Demonstrate edge removal
    cout << "\nRemoving the edge between vertices 1 and 3" << endl;
    g.removeEdge(1, 3);
    cout << "Graph after removing the edge:" << endl;
    g.print_graph();
    
    // Add the edge back
    cout << "\nAdding the edge back" << endl;
    g.addEdge(1, 3, 2);
    g.print_graph();
    
    // Demonstrate BFS
    cout << "\nDemonstrating BFS algorithm from vertex 0:" << endl;
    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.print_graph();
    
    // Demonstrate DFS
    cout << "\nDemonstrating DFS algorithm from vertex 0:" << endl;
    Graph dfsTree = Algorithms::dfs(g, 0);
    dfsTree.print_graph();
    
    // Demonstrate Dijkstra
    cout << "\nDemonstrating Dijkstra's algorithm from vertex 0:" << endl;
    Graph shortestPaths = Algorithms::dijkstra(g, 0);
    shortestPaths.print_graph();
    
    // Demonstrate Prim
    cout << "\nDemonstrating Prim's algorithm for minimum spanning tree:" << endl;
    Graph primMST = Algorithms::prim(g);
    primMST.print_graph();
    
    // Demonstrate Kruskal
    cout << "\nDemonstrating Kruskal's algorithm for minimum spanning tree:" << endl;
    Graph kruskalMST = Algorithms::kruskal(g);
    kruskalMST.print_graph();
    
    return 0;
}