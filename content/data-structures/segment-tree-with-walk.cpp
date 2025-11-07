/*
 *Description:*: Extends segment_tree with walk operation. Returns first index i >= l where ST[i] >= k, or -1 if none exists. Walk O(log n).
 *Status:* Partially tested
*/
template<class T, T m_(T, T)> struct segment_tree_with_walk : segment_tree<T,m_> {
  int walk(int l, T k) {
    vector<int> L, R;
    int r = this->n - 1;
    for (l += this->n, r += this->n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L.push_back(l++);
      if (r & 1) R.push_back(--r);
    }
    reverse(R.begin(), R.end());
    L.insert(L.end(), R.begin(), R.end());
    for (int v : L) {
      if (this->ST[v] >= k) {
        while (v < this->n) v = (this->ST[v << 1] >= k) ? (v << 1) : (v << 1 | 1);
        return v - this->n;
      }
    }
    return -1;
  }
};