template <typename T>
struct MergeSortTree {
  int N;
  vector<vector<T>> ST;
  void build(int n, int l, int r, vector<T> &vs) {
    if(l == r) ST[n] = {vs[l]};
    else {
      build(n * 2, l, (r + l) / 2, vs);
      build(n * 2 + 1, (r + l) / 2 + 1, r, vs);
      merge(ST[n*2].begin(), ST[n*2].end(), ST[n*2+1].begin(), ST[n*2+1].end(), back_inserter(ST[n]));
    }
  }
  MergeSortTree() {}
  MergeSortTree(vector<T> &vs) {
    N = vs.size();
    ST.resize(4 * N + 3);
    build(1, 0, N - 1, vs);
  }
  int query(int i, int j, int k) {
    return query(0, N - 1, 1, i, j, k);
  }
  int query(int l, int r, int n, int i, int j, int k) {
    if(l >= i && r <= j)
        return upper_bound(ST[n].begin(), ST[n].end(), k) - ST[n].begin();
    int mid = (r + l) / 2;
    if(mid < i) return query(mid + 1, r, n*2+1, i, j, k);
    if(mid >= j) return query(l, mid, n*2, i, j, k);
    return query(l, mid, n * 2, i, j, k) + query(mid + 1, r, n * 2 + 1, i, j, k);
  }
};
