template <class T>
struct SegmentTree {
  int N; vector<T> ST, lazy;
  vector<bool> bit; T (*merge)(T, T);
  void build(int n, int l, int r, vector<T> &vs) {
    if(l == r) ST[n] = vs[l];
    else {
      build(2 * n, l, (r + l) / 2, vs);
      build(2 * n + 1, (r + l) / 2 + 1, r, vs);
      ST[n] = merge(ST[n * 2], ST[n * 2 + 1]);
    }
  }
  SegmentTree(vector<T> &vs, T (*m)(T a, T b)) {
    merge = m; N = vs.size();
    ST.resize(4*N+3); lazy.assign(4*N+3, T());
    bit.assign(4*N+3, false); build(1, 0, N-1, vs);
  }
  void push(int n, int i, int j) {
    if(bit[n]) {
      ST[n] += lazy[n];
      if(i != j) {
        lazy[2 * n] += lazy[n]; 
        lazy[2 * n + 1] += lazy[n];
        bit[2 * n] = 1; bit[2 * n + 1] = 1;
      }
      lazy[n] = T(); bit[n] = 0;
    } 
  }
  void apply(int n, int i, int j, T val) {
    ST[n] += val;
    if(i != j) {
      lazy[2 * n] += val; 
      lazy[2 * n + 1] += val;
      bit[2 * n] = 1; bit[2 * n + 1] = 1;
    }
  }
  T query(int i, int j) {
    return query(0, N - 1, 1, i, j); }
  T query(int l, int r, int n, int i, int j) {
    push(n, l, r);
    if(i <= l && r <= j) return ST[n];
    int mid = (r + l) / 2;
    if(mid<i||j<l) return query(mid+1,r,2*n+1,i,j);
    if(mid>=j||r<i) return query(l, mid, 2*n, i, j);
    return merge(query(l, mid, 2 * n, i, j),
                 query(mid + 1, r, 2 * n + 1, i, j));
  }
  void update(int i, int j, T val) {
    update(0, N - 1, 1, i, j, val); }
  void update(int l,int r,int n,int i,int j, T val) {
    push(n, l, r);
    if(r < i || j < l) return;
    if(i <= l && r <= j) {
      apply(n, l, r, val); return;
    }
    int mid = (r + l) / 2;
    update(l, mid, 2 * n, i, j, val);
    update(mid + 1, r, 2 * n + 1, i, j, val);
    ST[n] = merge(ST[2 * n], ST[2 * n + 1]);
  }};