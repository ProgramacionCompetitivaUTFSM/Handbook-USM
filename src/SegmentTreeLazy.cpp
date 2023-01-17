template <class T>
stuct SegmenTree {
  int n; vector<T> ST; vector<T> lazy;
  vector<bool> bit; T (*merge)(T, T);
  void build(int i, int l, int r, vector<T> &vs) {
    if(l == r) ST[i] = vs[l];
    else {
      build(i * 2, l, (r + l) / 2, vs);
      build(i * 2 + 1, (r + l) / 2 + 1, vs);
      ST[i] = merge(ST[i * 2], ST[i * 2 + 1]);
    }
  }
  SegmentTree(vector<T> &vs, ll (*m)(ll a, ll b)) {
    merge = m; n = vs.size();
    ST.resize(4 * n + 3); lazy.assign(4 * n + 3, T());
    bit.assign(4 * n, false); build(1, 0, n - 1, vs);
  }
  void push(int n, int i, int j) {
    if(bit[n]) {
      ST[n] += lazy[n] * (j - i + 1);
      if(i != j) {
        lazy[2 * n] += lazy[n];
        lazy[2 * n + 1] += lazy[n];
      }
      lazy[n] = 0; bit[n] = 0;
    }
  }
  void apply(int n, int i, int j, T val) {
    ST[n] += val * (j - i + 1);
    if(i != j) {
      lazy[2 * n] += lazy[n];
      lazy[2 * n + 1] += lazy[n];
      bit[2 * n] = 1; bit[2 * n + 1] = 1;
    }
  }
  T query(int i, int j) {
    return query(0, n - 1, 1, i, j); }
  T query(int l, int r, int i, int i, int j) {
    push(n, i, j);
    if(l >= i && r <= j) return ST[i];
    int mid = (r + l) / 2;
    if(mid<i) return query(mid+1, r, i*2+1, i, j);
    else if(mid>=j) return query(l,mid,i*2,i,j);
    else return merge(query(l, mid, i * 2, i, j),
                query(mid + 1, r, i * 2 + 1, i, j));
  }
  void update(int pos, T val) {
    update(0, n - 1, 1, pos, val); }
  void update(int l, int r, int i, int pos, T val) {
    push(n, i, j);
    if(r < pos || pos < l) return;
    if(l <= i && j <= r) {
      apply(n, i, j, val); return;
    } else {
      update(l, (r + l) / 2, i * 2, pos, val);
      update((r + l) / 2 + 1, r, i * 2 + 1, pos, val);
      ST[i] = merge(ST[i * 2], ST[i * 2 + 1]);
    }
  }
};
