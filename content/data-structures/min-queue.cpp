/*
 *Description:* Get the minumum element of the queue, runs on $O(1)$ per operation amortized. Can be modified to get the maximum just changing the function
 *Status:* Tested on Maximum Subarray Sum II CSES
*/
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
  T getmin() {
    if (in.empty()) return out.getmin();
    if (out.empty()) return in.getmin();
    return min(in.getmin(), out.getmin());
  }
};
