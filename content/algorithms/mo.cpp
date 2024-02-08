/*
 *Description:* Allow us to answer queries offline with sqrt decomposition
 *Status:* Tested
*/
template<class T, class T2>
struct MoAlgorithm {
  vector<T> ans;
// data structure needs constructor to initialize empty
  MoAlgorithm(vector<T> &v, vector<Query> &queries,
              void (*add)(T2 &, T), void (*remove)(T2 &, T), T (*answer)(T2 &, Query)) {
    T2 ds(v.size());
    ans.assign(queries.size(), -1);
    sort(queries.begin(), queries.end());
    int l = 0;
    int r = -1;

    for (Query q : queries) {
      while (l > q.l) { l--; add(ds, v[l]); }
      while (r < q.r) { r++; add(ds, v[r]); }
      while (l < q.l) { remove(ds, v[l]); l++; }
      while (r > q.r) { remove(ds, v[r]); r--; }
      ans[q.i] = answer(ds, q);
    }
  }
};