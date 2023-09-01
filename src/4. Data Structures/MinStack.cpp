// Todas las operaciones son O(1)
template <typename T>
struct MinStack {
  stack<pair<T, T>> S;
  void push(T x) {
    T new_min = S.empty() ? x : min(x, S.top().second);
    S.push({x, new_min});
  }
  bool empty() { return S.empty(); }
  int size() { return S.size(); }
  void pop() { S.pop(); }
  T top() { return S.top().first; }
  T getMin() { return S.top().second; }
};
