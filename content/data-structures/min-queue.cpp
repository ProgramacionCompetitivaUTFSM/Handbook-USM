// Todas las operaciones son O(1)
template <typename T>
struct min_queue {
    MinStack<T> in, out;
    void push(T x) { in.push(x); }
    bool empty() { return in.empty() && out.empty(); }
    int size() { return in.size() + out.size(); }
    void pop() {
        if (out.empty()) {
            while (!in.empty()) {
                out.push(in.top());
                in.pop();
            }
        }
        out.pop();
    }
    T front() {
        if (!out.empty()) return out.top();
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
        return out.top();
    }
    T getMin() {
        if (in.empty()) return out.getMin();
        if (out.empty()) return in.getMin();
        return min(in.getMin(), out.getMin());
    }
};