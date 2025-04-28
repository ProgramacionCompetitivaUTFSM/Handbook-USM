/*
 *Description:* Iterative merge sort tree. Each node stores sorted elements in its range.
  - Query: Count elements > k in range [i, j]. O(log^2 n) per operation.
  - Build: O(n log n)
 *Status:* Distinct Values Queries (CSES)
*/
template <typename T>
struct merge_sort_tree {
  int N; vector<vector<T>> ST;
  merge_sort_tree(){}
  merge_sort_tree(vector<T> &vs) {
    N = vs.size(); ST.resize(2 * N);
    for (int i = 0; i < N; i++) ST[i + N] = {vs[i]};
    for (int i = N - 1; i > 0; i--)
      merge(ST[i<<1].begin(), ST[i<<1].end(), ST[i<<1|1].begin(), ST[i<<1|1].end(), back_inserter(ST[i]));
  }
  int query(int i, int j, int k) {
    int res = 0;
    for (i += N, j += N + 1; i < j; i >>= 1, j >>= 1) {
      if (i & 1) res += ST[i].size() - (upper_bound(ST[i].begin(), ST[i].end(), k) - ST[i].begin()), i++;
      if (j & 1) --j, res += ST[j].size() - (upper_bound(ST[j].begin(), ST[j].end(), k) - ST[j].begin());
    }
    return res;
  }
};
