/*
 *Description:* Dynamically insert a*x + b lines and query for maximum at any x and operations have complexity O(log N)
 *Status:* Tested on CSES
*/
struct Line {
    mutable int a, b, c;
    bool operator<(Line r) const { return a < r.a; }
    bool operator<(int x) const { return c < x; }
};
struct LineContainer : multiset<Line, less<>> {
    int div(int a, int b) {
        return a / b - ((a ^ b) < 0 && a % b);
    }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->c = INF, 0;
        if (x->a == y->a) x->c = x->b > y->b ? INF : -INF;
        else x->c = div(y->b - x->b, x->a - y->a);
        return x->c >= y->c;
    }
    void add(int a, int b) {
        // a *= -1, b *= -1 // for min
        auto z = insert({a, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->c >= y->c) isect(x, erase(y));
    }
    int query(int x) {
        if (empty()) return -INF; // INF for min
        auto l = *lower_bound(x);
        return l.a * x + l.b;
        // return -l.a * x - l.b; // for min
    }
};