/*
 *Description:* The nodes are created when the some value is updated, enabling queries in intervals like $[0, 10^12]$. Overall complexity is $O(Q log N)$
 *Status:* Not tested
*/
template <
    class T,           // Data type of the nodes
    class MAXi,        // Data type of the ranges (ll or i128)
    T merge(T, T),     // Merge
    T init(MAXi, MAXi) // Default value for [a, b]
>
struct dynamic_segment_tree {
  vector<T> ST; vector<int>L, R;
  MAXi n; int n_count;
  dynamic_segment_tree (MAXi n, int r) : 
    n(n),n_count(1),L(1),R(1),ST(1){
    ST.reserve(r);
    L.reserve(r);
    R.reserve(r);
    ST[0] = init(0, n - 1);
  }
  int addNode(MAXi l, MAXi r){
    L.push_back(0);
    R.push_back(0);
    ST.push_back(init(l, r));
    return n_count ++;
  }
  T query(int i, MAXi l, MAXi r, MAXi a, MAXi b) {
    if (a <= l and r <= b)
      return ST[i];
    MAXi mid = ((l + r) >> 1LL);
    if (b <= mid) 
      return (L[i] != 0 ? query(L[i], l, mid, a, b) : init(l, mid));
    else if (a > mid)
      return (R[i] != 0 ? query(R[i], mid + 1, r, a, b) : init(mid + 1, r));
    if (L[i] == 0) L[i] = addNode(l, mid);
    if (R[i] == 0) R[i] = addNode(mid + 1, r);
    return merge(query(L[i], l, mid, a, b), query(R[i], mid + 1, r, a, b));
  }
  T query(MAXi a, MAXi b) {
    return query(0, 0, n - 1, a, b);
  }
  void update(int i, MAXi l, MAXi r, MAXi p, T v) {
    if (l == r){
      ST[i] = v; return;
    }
    MAXi mid = (l + r) / 2LL;
    if (p <= mid)
      update(L[i] != 0 ? L[i] : L[i] = addNode(l, mid), l, mid, p, v);
    else 
      update(R[i] != 0 ? R[i] : R[i] = addNode(mid + 1, r), mid + 1, r, p, v);
    ST[i] = merge(
        L[i] != 0 ? ST[L[i]] : init(l, mid), 
        R[i] != 0 ? ST[R[i]] : init(mid + 1, r)
      );
  }
  void update(MAXi pos, T v) {
    update(0, 0, n - 1, pos, v);
  }
};