// PriorityQueue.hpp - הגדרת מחלקת תור עדיפויות

#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

namespace graph {

/**
 * מחלקה המייצגת תור עדיפויות מינימלי.
 * משמשת לאלגוריתמים Dijkstra ו-Prim.
 */
class PriorityQueue {
private:
    struct Node {
        int vertex;     ///< מספר הקודקוד
        int priority;   ///< ערך העדיפות (משקל)
    };
    
    Node* heap;         ///< מערך המייצג ערימה בינארית
    int capacity;       ///< קיבולת התור
    int size;           ///< מספר האיברים הנוכחי בתור
    int* positions;     ///< מערך המכיל את המיקום של כל קודקוד בערימה
    
    /**
     * מחליף שני איברים בערימה ומעדכן את מערך המיקומים.
     * @param i אינדקס האיבר הראשון
     * @param j אינדקס האיבר השני
     */
    void swap(int i, int j);
    
    /**
     * מתקן את הערימה כלפי מעלה מהאינדקס הנתון.
     * @param index האינדקס ממנו להתחיל את התיקון
     */
    void heapifyUp(int index);
    
    /**
     * מתקן את הערימה כלפי מטה מהאינדקס הנתון.
     * @param index האינדקס ממנו להתחיל את התיקון
     */
    void heapifyDown(int index);
    
    /**
     * מחזיר את האינדקס של האב של האיבר באינדקס הנתון.
     * @param index האינדקס של האיבר
     * @return האינדקס של האב
     */
    int parent(int index) const;
    
    /**
     * מחזיר את האינדקס של הבן השמאלי של האיבר באינדקס הנתון.
     * @param index האינדקס של האיבר
     * @return האינדקס של הבן השמאלי
     */
    int leftChild(int index) const;
    
    /**
     * מחזיר את האינדקס של הבן הימני של האיבר באינדקס הנתון.
     * @param index האינדקס של האיבר
     * @return האינדקס של הבן הימני
     */
    int rightChild(int index) const;

public:
    /**
     * בנאי למחלקת PriorityQueue.
     * @param capacity קיבולת התור
     */
    explicit PriorityQueue(int capacity);
    
    /**
     * מפרק (destructor).
     */
    ~PriorityQueue();
    
    /**
     * מוסיף קודקוד לתור עם ערך עדיפות נתון.
     * @param vertex מספר הקודקוד
     * @param priority ערך העדיפות
     * @throws std::overflow_error אם התור מלא
     * @throws std::invalid_argument אם הקודקוד כבר קיים בתור
     */
    void insert(int vertex, int priority);
    
    /**
     * מוציא ומחזיר את הקודקוד עם העדיפות הנמוכה ביותר.
     * @return מספר הקודקוד
     * @throws std::underflow_error אם התור ריק
     */
    int extractMin();
    
    /**
     * מעדכן את ערך העדיפות של קודקוד.
     * @param vertex מספר הקודקוד
     * @param priority ערך העדיפות החדש
     * @throws std::invalid_argument אם הקודקוד אינו קיים בתור
     */
    void decreaseKey(int vertex, int priority);
    
    /**
     * בודק אם התור ריק.
     * @return true אם התור ריק, אחרת false
     */
    bool isEmpty() const;
    
    /**
     * בודק אם קודקוד קיים בתור.
     * @param vertex מספר הקודקוד
     * @return true אם הקודקוד קיים בתור, אחרת false
     */
    bool contains(int vertex) const;
};

} // namespace graph

#endif // PRIORITY_QUEUE_HPP
