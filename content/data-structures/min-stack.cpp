/*
 *Description:* Get the minumum element of the stack, runs on $O(1)$ $O(1)$ per operation amortized. Can be modified to get the maximum just changing the function
 *Status:* Tested on Maximum Subarray Sum II CSES
*/
template <typename T>
struct min_stack {
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