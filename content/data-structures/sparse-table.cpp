/*
 *Description:* Range queries, precomputed $O(n log n)$, query $O(1)$.
 - Only supports queries of idempotent functions (min, max, gcd)
 - Does not allow updates
 *Status:* Highly tested
*/
template <typename T>
struct sparse_table {
  int n;
  vector<vector<T>> table;
  function<T(T, T)> merge;
  sparse_table(const vector<T> &arr, function<T(T, T)> m) : merge(m) {
    n = arr.size();
    int k = log2_floor(n) + 1;
    table.assign(n, vector<T>(k));
    for (int i = 0; i < n; i++)
      table[i][0] = arr[i];
    for (int j = 1; j < k; j++)
      for (int i = 0; i + (1 << j) <= n; i++)
        table[i][j] = merge(table[i][j-1], table[i+(1<<(j-1))][j-1]);
  }
  T query(int l, int r) {
    int k = log2_floor(r - l + 1);
    return merge(table[l][k], table[r-(1 << k)+1][k]);
  }
  int log2_floor(int n) { return n ? __builtin_clzll(1) - __builtin_clzll(n) : -1; }
};