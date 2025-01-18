/*
 *Description:* Allow us to answer queries and updates offline with block decomposition in $O(q \cdot n^{\frac{2}{3}})$
 *Status:* Not tested 
*/
struct query {
  int l,r,t,i;
};
template<class T, typename U, class T2>
struct mo_update {
  vector<U> ans;
  mo_update(vector<T> &v, vector<query> &queries, vector<pair<int,T>> & updates, T2 & ds) {
    ds.init(v,updates);
    int block_sz = cbrtl(2*v.size()*v.size());
    ans.assign(queries.size(),-1);
    sort(queries.begin(), queries.end(), [&](auto a, auto b){
      if (a.l/block_sz == b.l/block_sz){
        if (a.r/block_sz == b.r/block_sz) return a.t < b.t;
        return a.r/block_sz < b.r/block_sz;
      }
      return a.l/block_sz < b.l/block_sz;
    });
    int l = 0, r = -1;
    for (query q : queries) {
      while (ds.t < q.t) ds.update(l,r);
      while (ds.t > q.t) ds.rollback(l,r);
      while (l > q.l) ds.add(--l);
      while (r < q.r) ds.add(++r);
      while (l < q.l) ds.remove(l++);
      while (r > q.r) ds.remove(r--);
      ans[q.i] = ds.answer(q);
    }
  }
};