/*
 *Description:* Get the minumum element of the stack, runs on $O(1)$ $O(1)$ per operation amortized. Can be modified to get the maximum just changing the function
 *Status:* Tested on Maximum Subarray Sum II CSES
*/
template <typename T>
struct min_stack {
  vector<pair<T, T>> S;
  void push(T x) {
    T new_min = S.empty() ? x : min(x, S.back().second);
    S.push_back({x, new_min});
  }
  bool empty() { return S.empty(); }
  int size() { return S.size(); }
  void pop() { S.pop_back(); }
  T top() { return S.back().first; }
  T getmin() { return S.back().second; }
  void swap(min_stack & other) noexcept { S.swap(other.S); }
};
