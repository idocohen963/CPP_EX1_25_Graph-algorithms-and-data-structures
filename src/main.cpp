#include <iostream>
#include "../include/Graph.hpp"
#include "../include/Algorithms.hpp"

using namespace graph;
using namespace std;

int main() {
    // יצירת גרף לדוגמה
    cout << "יצירת גרף לדוגמה עם 6 קודקודים" << endl;
    Graph g(6);
    
    // הוספת צלעות
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    
    // הדפסת הגרף
    cout << "\nהגרף המקורי:" << endl;
    g.print_graph();
    
    // הדגמת הסרת צלע
    cout << "\nהסרת הצלע בין קודקודים 1 ו-3" << endl;
    g.removeEdge(1, 3);
    cout << "הגרף לאחר הסרת הצלע:" << endl;
    g.print_graph();
    
    // הוספת הצלע בחזרה
    cout << "\nהוספת הצלע בחזרה" << endl;
    g.addEdge(1, 3, 2);
    
    // הדגמת BFS
    cout << "\nהדגמת אלגוריתם BFS מקודקוד 0:" << endl;
    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.print_graph();
    
    // הדגמת DFS
    cout << "\nהדגמת אלגוריתם DFS מקודקוד 0:" << endl;
    Graph dfsTree = Algorithms::dfs(g, 0);
    dfsTree.print_graph();
    
    // הדגמת Dijkstra
    cout << "\nהדגמת אלגוריתם Dijkstra מקודקוד 0:" << endl;
    Graph shortestPaths = Algorithms::dijkstra(g, 0);
    shortestPaths.print_graph();
    
    // הדגמת Prim
    cout << "\nהדגמת אלגוריתם Prim למציאת עץ פורש מינימלי:" << endl;
    Graph primMST = Algorithms::prim(g);
    primMST.print_graph();
    
    // הדגמת Kruskal
    cout << "\nהדגמת אלגוריתם Kruskal למציאת עץ פורש מינימלי:" << endl;
    Graph kruskalMST = Algorithms::kruskal(g);
    kruskalMST.print_graph();
    
    return 0;
}
