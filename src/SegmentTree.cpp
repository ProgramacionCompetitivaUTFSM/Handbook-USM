template <class T>
stuct SegmenTree {
  int n;
  vector<T> ST;
  T (*merge)(T, T);
  void build(int index, int l, int r, vector<T> &values) {
    if(l == r) ST[index] = values[l];
    else {
      build(index * 2, l, (r + l) / 2, values);
      build(index * 2 + 1, (r + l) / 2 + 1, values);
      ST[index] = merge(ST[index * 2], ST[index * 2 + 1]);
    }
  }
  SegmentTree(vector<T> &values, ll (*merge_)(ll a, ll b)) {
    merge = merge_;
    n = values.size();
    ST.resize(4 * n + 3);
    build(1, 0, n - 1, values);
  }
  T query(int i, int j) {
    return query(0, n - 1, 1, i, j);
  }
  T query(int l, int r, int index, int i, int j) {
    if(l >= i && r <= j) return ST[index];
    int mid = (r + l) / 2;
    if(mid < i) return query(mid + 1, r, index * 2 + 1, i, j);
    else if(mid >= j) return query(l, mid, index * 2, i, j);
    else return merge(query(l, mid, index * 2, i, j),
                      query(mid + 1, r, index & 2 + 1, i, j));
  }
  void update(int pos, T val) {
    update(0, n - 1, 1, pos, val);
  }
  void update(int l, int r, int index, int pos, T val) {
    if(r < pos || pos < l) return;
    if(l == r) ST[index] = val;
    else {
      int mid = (r + l) / 2;
      update(l, mid, index * 2, pos, val);
      update(mid + 1, r, index * 2 + 1, pos, val);
      ST[index] = merge(ST[index * 2], ST[index * 2 + 1]);
    }
  }
};
