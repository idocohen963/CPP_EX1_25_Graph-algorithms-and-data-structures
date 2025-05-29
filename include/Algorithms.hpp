// Algorithms.hpp - הגדרת מחלקת Algorithms המכילה אלגוריתמים על גרפים

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"

namespace graph {

/**
 * מחלקה המכילה אלגוריתמים על גרפים.
 * כל הפונקציות הן סטטיות.
 */
class Algorithms {
public:
    /**
     * מבצע סריקת רוחב (BFS) על גרף ומחזיר עץ BFS.
     * @param g הגרף לסריקה
     * @param source קודקוד המקור
     * @return עץ BFS
     * @throws std::out_of_range אם קודקוד המקור אינו תקין
     */
    static Graph bfs(const Graph& g, int source);
    
    /**
     * מבצע סריקת עומק (DFS) על גרף ומחזיר עץ או יער DFS.
     * @param g הגרף לסריקה
     * @param source קודקוד המקור
     * @return עץ או יער DFS
     * @throws std::out_of_range אם קודקוד המקור אינו תקין
     */
    static Graph dfs(const Graph& g, int source);
    
    /**
     * מבצע אלגוריתם דייקסטרה למציאת מסלולים קצרים ביותר.
     * @param g הגרף לסריקה
     * @param source קודקוד המקור
     * @return עץ של מסלולים קצרים ביותר
     * @throws std::out_of_range אם קודקוד המקור אינו תקין
     * @throws std::invalid_argument אם הגרף מכיל משקלים שליליים
     */
    static Graph dijkstra(const Graph& g, int source);
    
    /**
     * מבצע אלגוריתם פרים למציאת עץ פורש מינימלי.
     * @param g הגרף לסריקה
     * @return עץ פורש מינימלי
     * @throws std::invalid_argument אם הגרף אינו קשיר
     */
    static Graph prim(const Graph& g);
    
    /**
     * מבצע אלגוריתם קרוסקל למציאת עץ פורש מינימלי.
     * @param g הגרף לסריקה
     * @return עץ פורש מינימלי
     */
    static Graph kruskal(const Graph& g);

private:
    /**
     * פונקציית עזר לאלגוריתם DFS.
     * @param g הגרף לסריקה
     * @param vertex הקודקוד הנוכחי
     * @param visited מערך המסמן אילו קודקודים כבר נסרקו
     * @param parent מערך המכיל את האב של כל קודקוד בעץ DFS
     * @param dfsTree עץ ה-DFS הנבנה
     */
    static void dfsVisit(const Graph& g, int vertex, bool* visited, int* parent, Graph& dfsTree);
    
    /**
     * בודק אם הגרף מכיל משקלים שליליים.
     * @param g הגרף לבדיקה
     * @return true אם הגרף מכיל משקלים שליליים, אחרת false
     */
    static bool hasNegativeWeights(const Graph& g);
    
    /**
     * בודק אם הגרף קשיר.
     * @param g הגרף לבדיקה
     * @return true אם הגרף קשיר, אחרת false
     */
    static bool isConnected(const Graph& g);
    
    /**
     * מבנה המייצג צלע עם מקור, יעד ומשקל.
     * משמש לאלגוריתם קרוסקל.
     */
    struct Edge {
        int src;     ///< קודקוד המקור
        int dest;    ///< קודקוד היעד
        int weight;  ///< משקל הצלע
        
        /**
         * אופרטור השוואה לצורך מיון.
         * @param other הצלע להשוואה
         * @return true אם המשקל של הצלע הנוכחית קטן מהמשקל של הצלע האחרת
         */
        bool operator<(const Edge& other) const {
            return weight < other.weight;
        }
    };

    /**
     * ממיינת מערך של צלעות לפי משקל (מיון בחירה).
     * @param edges מערך הצלעות
     * @param edgeCount מספר הצלעות במערך
     */
    static void SortEdges(Edge* edges, int edgeCount);
};

} // namespace graph

#endif // ALGORITHMS_HPP
