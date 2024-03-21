/*
 *Description:* Allow us to answer queries offline with sqrt decomposition
 *Status:* Tested
*/
struct query {
  ll l, r, i;
};
template<class T, class T2, void add(T2&, T), void rem(T2&, T), T answer(T2&, query)>
struct mo_algorithm {
  vector<T> ans;
  mo_algorithm(vector<T> &v, vector<query> &queries) {
    ll block_sz = 1;
    T2 ds(v.size());
    ans.assign(queries.size(), -1);
    block_sz = sqrtl(v.size());
    sort(queries.begin(), queries.end(), [&](auto &a, auto &b) {
      int ba = a.l/block_sz;
      int bb = b.l/block_sz;
      if(ba != bb) return ba < bb;
      return (ba&1) ? (a.r<b.r) : (a.r>b.r);
    }); 
    int l = 0, r = -1;
    for (query q : queries) {
      while (l > q.l) l--, add(ds, v[l]);
      while (r < q.r) r++, add(ds, v[r]);
      while (l < q.l) remove(ds, v[l]), l++;
      while (r > q.r) remove(ds, v[r]), r--;
      ans[q.i] = answer(ds, q);
    }
  }
};
