// Queue.hpp - הגדרת מחלקת תור בסיסית

#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace graph {

/**
 * מחלקה המייצגת תור בסיסי.
 * משמשת לאלגוריתם BFS.
 */
class Queue {
private:
    int* array;      ///< מערך לאחסון הערכים
    int capacity;    ///< קיבולת התור
    int front;       ///< אינדקס הערך הראשון בתור
    int rear;        ///< אינדקס המקום הפנוי הבא בתור
    int size;        ///< מספר האיברים הנוכחי בתור

public:
    /**
     * בנאי למחלקת Queue.
     * @param capacity קיבולת התור
     */
    explicit Queue(int capacity);
    
    /**
     * מפרק (destructor).
     */
    ~Queue();
    
    /**
     * מוסיף ערך לסוף התור.
     * @param value הערך להוספה
     * @throws std::overflow_error אם התור מלא
     */
    void enqueue(int value);
    
    /**
     * מוציא ומחזיר את הערך בראש התור.
     * @return הערך בראש התור
     * @throws std::underflow_error אם התור ריק
     */
    int dequeue();
    
    /**
     * מחזיר את הערך בראש התור מבלי להוציאו.
     * @return הערך בראש התור
     * @throws std::underflow_error אם התור ריק
     */
    int peek() const;
    
    /**
     * בודק אם התור ריק.
     * @return true אם התור ריק, אחרת false
     */
    bool isEmpty() const;
    
    /**
     * בודק אם התור מלא.
     * @return true אם התור מלא, אחרת false
     */
    bool isFull() const;
    
    /**
     * מחזיר את מספר האיברים בתור.
     * @return מספר האיברים
     */
    int getSize() const;
};

} // namespace graph

#endif // QUEUE_HPP
