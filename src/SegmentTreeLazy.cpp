template <class T>
stuct SegmenTree {
  int N; vector<T> ST, lazy;
  vector<bool> bit; T (*merge)(T, T);
  void build(int n, int l, int r, vector<T> &vs) {
    if(l == r) ST[n] = vs[l];
    else {
      build(n * 2, l, (r + l) / 2, vs);
      build(n * 2 + 1, (r + l) / 2 + 1, vs);
      ST[n] = merge(ST[n * 2], ST[n * 2 + 1]);
    }
  }
  SegmentTree(vector<T> &vs, ll (*m)(ll a, ll b)) {
    merge = m;
    N = vs.size();
    ST.resize(4 * n + 3);
    lazy.assign(4 * n + 3, T());
    bit.assign(4 * n + 3, false);
    build(1, 0, n - 1, vs);
  }
  void push(int n, int i, int j) {
    if(bit[n]) {
      ST[n] += lazy[n] * (j - i + 1);
      if(i != j) {
        lazy[2 * n] += lazy[n];
        lazy[2 * n + 1] += lazy[n];
      }
      lazy[n] = 0;
      bit[n] = 0;
    } 
  }
  void apply(int n, int i, int j, T val) {
    ST[n] += val * (j - i + 1);
    if(i != j) {
      lazy[2 * n] += val;
      lazy[2 * n + 1] += val;
      bit[2 * n] = 1;
      bit[2 * n + 1] = 1;
    }
  }
  T query(int i, int j) {
    return query(0, n - 1, 1, i, j); }
  T query(int l, int r, int n, int i, int j) {
    push(n, l, r);
    if(l >= i && r <= j) return ST[n];
    int mid = (r + l) / 2;
    if(mid < i) return query(mid + 1, r, n * 2 + 1, i, j);
    else if(mid >= j) return query(l, mid, n * 2, i, j);
    else return merge(query(l, mid, n * 2, i, j),
                      query(mid + 1, r, n & 2 + 1, i, j));
  }
  void update(int i, int j, T val) {
    update(0, n - 1, 1, i, j, val); }
  void update(int l, int r, int n, int i, int j, T val) {
    push(n, l, r);
    if(i < r || l < j) return;
    if(i <= l && r <= j) {
      apply(n, l, r, val);
      return;
    } else {
      int mid = (r + l) / 2;
      update(l, mid, n * 2, i, j, val);
      update(mid + 1, r, n * 2 + 1, i, j, val);
      ST[n] = merge(ST[n * 2], ST[n * 2 + 1]);
    }
  }
};
