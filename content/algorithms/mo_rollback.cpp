/*
 *Description:* Allow us to answer queries offline with sqrt decomposition
 *Status:* Tested
*/
struct query {
  ll l, r, i;
};

template<typename T, typename U, class T2>
struct rollback_mo_algorithm {
  vector<U> ans;
  template<typename... Args>
  rollback_mo_algorithm(vector<T> &v, vector<query> &queries, Args... args) {
    ll block_sz = sqrtl(v.size());
    ans.resize(queries.size());
    T2 ds(args...);
    sort(queries.begin(), queries.end(), [&](auto &a, auto &b) {
      return a.l/block_sz != b.l/block_sz ? a.l/block_sz < b.l/block_sz : a.r < b.r;
    });
    ll t = 0, last, border, last_block = -1, block;
    for(ll i = 0; i < queries.size(); i++) {
      block = queries[i].l / block_sz;
      if (block == queries[i].r/block_sz) {
        T2 tmp(args...);
        for (ll k = queries[i].l; k <= queries[i].r; k++)
          tmp.add(v[k]);
        ans[queries[i].i] = tmp.answer(queries[i]);
        continue;
      }
      if(last_block != block) {
        ds = T2(args...);
        border = block_sz * (block + 1);
        last = border;
      }
      last_block = block;
      for(ll k = last + 1; k <= queries[i].r; k++) ds.add(v[k]);
      t = ds.snapshot();
      for(ll k = queries[i].l; k <= border; k++) ds.add(v[k]);
      ans[queries[i].i] = ds.answer(queries[i]);
      ds.rollback(t);
      last = queries[i].r;
    }
  }
};