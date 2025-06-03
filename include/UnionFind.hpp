// idocohen963@gmail.com

#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP

namespace graph {

/**
 * מחלקה המייצגת מבנה נתונים Union-Find.
 * משמשת לאלגוריתם Kruskal.
 */
class UnionFind {
private:
    int* parent;    ///< מערך המכיל את האב של כל איבר
    int* rank;      ///< מערך המכיל את הדרגה של כל איבר
    int size;       ///< מספר האיברים

public:
    /**
     * בנאי למחלקת UnionFind.
     * @param size מספר האיברים
     */
    explicit UnionFind(int size);
    
    /**
     * מפרק (destructor).
     */
    ~UnionFind();
    
    /**
     * מוצא את הנציג של הקבוצה אליה שייך האיבר.
     * @param x האיבר
     * @return הנציג של הקבוצה
     */
    int find(int x);
    
    /**
     * מאחד את הקבוצות של שני איברים.
     * @param x האיבר הראשון
     * @param y האיבר השני
     * @return true אם האיחוד בוצע, false אם האיברים כבר באותה קבוצה
     */
    bool unionSets(int x, int y);
};

} // namespace graph

#endif // UNION_FIND_HPP
