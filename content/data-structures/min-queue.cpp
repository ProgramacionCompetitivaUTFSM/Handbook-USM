template <typename T>
struct min_queue {
  min_stack<T> in, out;
  void push(T x) { in.push(x); }
  bool empty() { return in.empty() and out.empty(); }
  int size() { return in.size() + out.size(); }
  void pop() {
    if (out.empty())
    for (;in.size(); in.pop()) out.push(in.top());
    out.pop();
  }
  T front() {
    if (!out.empty()) return out.top();
    for (;in.size(); in.pop()) out.push(in.top());
    return out.top();
  }
  T getMin() {
    if (in.empty()) return out.getMin();
    if (out.empty()) return in.getMin();
    return min(in.getMin(), out.getMin());
  }
};
