/*
 *Description:* Range queries, build $O(n)$, query $O(1)$, positions [0, n - 1], merge must be overlapping friendly, for example min,max,gcd and lcm
 *Status:* Tested on CSES
*/
template<class T, T merge(T,T)>
struct range_query {
  int n,sz,ld,bl; vector<int> q;
  vector<vector<T>> st; vector<T> arr;
  range_query(vector<T> & a){
    n = a.size(); sz = log2(n);
    bl = (n+sz-1)/sz; ld = log2(bl); arr = a;
    st.assign(bl,vector<T>(ld+1)); q.resize(n);
    for (int i = 0; i < n; i++){
      st[i/sz][0] = ((i%sz == 0)?a[i]:merge(st[i/sz][0],a[i]));
      int last = a[i]; q[i] = ((i > 0)?q[i-1]:0);
      while (q[i] != 0 && merge(a[i-1-__builtin_ctz(q[i])],last) == last)
        q[i] ^= (1<<__builtin_ctz(q[i]));
      q[i] = (q[i]<<1|1); q[i] &= (1<<sz)-1;
    }
    for (int i = 1; i <= ld; i++)
      for (int j = 0; j < bl-(1<<(i-1)); j++)
        st[j][i] = merge(st[j][i-1],st[j+(1<<(i-1))][i-1]);
  }
  T spquery(int l, int r){
    int lsz = log2(r-l+1);
    return merge(st[l][lsz],st[r-(1<<lsz)+1][lsz]);
  }
  T query(int l, int r){
    if (l/sz == r/sz)
      return arr[r-(31-__builtin_clz(q[r]&((1<<(r-l+1))-1)))];
    T res; bool hasR = 0;
    int ql = (l+sz-1)/sz, qr = (r/sz)-1;
    if (ql <= qr) res = spquery(ql,qr), hasR = 1;
    int pl = ql*sz-1, pr = (qr+1)*sz;
    if (l <= pl){
      int vl = arr[pl-(31-__builtin_clz(q[pl]&((1<<(pl-l+1))-1)))];
      res = (hasR?merge(res,vl):vl), hasR = 1;
    }
    if (pr <= r){
      int vr = arr[r-(31-__builtin_clz(q[r]&((1<<(r-pr+1))-1)))];
      res = (hasR?merge(res,vr):vr), hasR = 1;
    }
    return res;
  }
};