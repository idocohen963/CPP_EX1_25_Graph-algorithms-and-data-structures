// Graph.hpp - הגדרת מחלקת Graph המייצגת גרף באמצעות רשימת שכנויות

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>

namespace graph {

/**
 * מחלקה המייצגת גרף לא מכוון באמצעות רשימת שכנויות.
 * הגרף מאותחל עם מספר קודקודים קבוע שלא ניתן לשנות.
 */
class Graph {
private:
    /**
     * מבנה המייצג צלע ברשימת השכנויות.
     */
    struct EdgeNode {
        int dest;       ///< מספר הקודקוד היעד
        int weight;     ///< משקל הצלע
        EdgeNode* next; ///< מצביע לצלע הבאה ברשימה

        /**
         * בנאי למבנה EdgeNode.
         * @param dest מספר הקודקוד היעד
         * @param weight משקל הצלע
         * @param next מצביע לצלע הבאה ברשימה
         */
        EdgeNode(int dest, int weight, EdgeNode* next = nullptr)
            : dest(dest), weight(weight), next(next) {}
    };

    int numVertices;       ///< מספר הקודקודים בגרף
    EdgeNode** adjList;    ///< מערך של רשימות שכנויות

    /**
     * בודק אם מספר הקודקוד תקין.
     * @param v מספר הקודקוד לבדיקה
     * @throws std::out_of_range אם מספר הקודקוד אינו תקין
     */
    void validateVertex(int v) const;

public:
    /**
     * בנאי למחלקת Graph.
     * @param numVertices מספר הקודקודים בגרף
     * @throws std::invalid_argument אם מספר הקודקודים אינו חיובי
     */
    explicit Graph(int numVertices);

    /**
     * בנאי העתקה.
     * @param other הגרף לעתיקה
     */
    Graph(const Graph& other);

    /**
     * אופרטור השמה.
     * @param other הגרף להשמה
     * @return הפניה לגרף הנוכחי
     */
    Graph& operator=(const Graph& other);

    /**
     * מפרק (destructor).
     */
    ~Graph();

    /**
     * מוסיף צלע לא מכוונת בין שני קודקודים.
     * @param src מספר קודקוד המקור
     * @param dest מספר קודקוד היעד
     * @param weight משקל הצלע (ברירת מחדל: 1)
     * @throws std::out_of_range אם אחד ממספרי הקודקודים אינו תקין
     * @throws std::invalid_argument אם הצלע כבר קיימת או אם מדובר בלולאה עצמית
     */
    void addEdge(int src, int dest, int weight = 1);

    /**
     * מסיר צלע לא מכוונת בין שני קודקודים.
     * @param src מספר קודקוד המקור
     * @param dest מספר קודקוד היעד
     * @throws std::out_of_range אם אחד ממספרי הקודקודים אינו תקין
     * @throws std::invalid_argument אם הצלע אינה קיימת
     */
    void removeEdge(int src, int dest);

    /**
     * מדפיס את הגרף בפורמט קריא.
     */
    void print_graph() const;

    /**
     * בודק אם קיימת צלע בין שני קודקודים.
     * @param src מספר קודקוד המקור
     * @param dest מספר קודקוד היעד
     * @return true אם הצלע קיימת, אחרת false
     * @throws std::out_of_range אם אחד ממספרי הקודקודים אינו תקין
     */
    bool hasEdge(int src, int dest) const;

    /**
     * מחזיר את מספר הקודקודים בגרף.
     * @return מספר הקודקודים
     */
    int getNumVertices() const;

    /**
     * מחזיר מצביע לרשימת השכנים של קודקוד.
     * @param v מספר הקודקוד
     * @return מצביע לרשימת השכנים
     * @throws std::out_of_range אם מספר הקודקוד אינו תקין
     */
    const EdgeNode* getNeighbors(int v) const;

    /**
     * מחזיר את מספר השכנים של קודקוד.
     * @param v מספר הקודקוד
     * @return מספר השכנים
     * @throws std::out_of_range אם מספר הקודקוד אינו תקין
     */
    int getNumNeighbors(int v) const;

    // מאפשר לאלגוריתמים לגשת למבנה EdgeNode
    friend class Algorithms;
};

} // namespace graph

#endif // GRAPH_HPP
