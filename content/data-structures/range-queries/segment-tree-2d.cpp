/*
 *Description:* 2D Range queries, Runs on $O(log n dot log m)$ per operation
 *Status:* Tested
*/
template<class T, T merge(T,T)>
struct segment_tree2d {
  int n,m; vector<vector<T>> st;
  segment_tree2d(){}
  segment_tree2d(vector<vector<T>> & a){
    n = a.size(), m = a[0].size(); st.assign(n<<1,vector<T>(m<<1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) st[i+n][j+m] = a[i][j];
      for (int j = m-1; j > 0; j--) st[i+n][j] = merge(st[i+n][j<<1],st[i+n][j<<1|1]);
    }
    for (int i = n-1; i > 0; i--){
      for (int j = 0; j < m; j++) st[i][j+m] = merge(st[i<<1][j+m],st[i<<1|1][j+m]);
      for (int j = m-1; j > 0; j--) st[i][j] = merge(st[i][j<<1],st[i][j<<1|1]);
    }
  }
  void update(int i, int j, T val){
    st[i += n][j += m] = val;
    for (int jj = (j>>1); jj > 0; jj >>= 1) 
    st[i][jj] = merge(st[i][jj<<1],st[i][jj<<1|1]);
    for (i >>= 1; i > 0; i >>= 1){
      st[i][j] = merge(st[i<<1][j],st[i<<1|1][j]);
      for (int jj = (j>>1); jj > 0; jj >>= 1) 
      st[i][jj] = merge(st[i][jj<<1],st[i][jj<<1|1]);
    }
  }
  T query_help(int i, int l, int r){
    T ansL, ansR; bool hasL = 0, hasR = 0;
    for (l += m, r += m+1; l < r; l >>= 1, r >>= 1){
      if (l&1) ansL = (hasL?merge(ansL,st[i][l++]):st[i][l++]), hasL = 1;
      if (r&1) ansR = (hasR?merge(st[i][--r],ansR):st[i][--r]), hasR = 1;
    }        
    if (!hasL) return ansR; if (!hasR) return ansL;
    return merge(ansL,ansR);
  }    
  T query(int l1, int r1, int l2, int r2){
    T ansL, ansR; bool hasL = 0, hasR = 0;
    for (l1 += n, r1 += n+1; l1 < r1; l1 >>= 1, r1 >>= 1){
      if (l1&1) ansL = (hasL?merge(ansL,query_help(l1++,l2,r2)):query_help(l1++,l2,r2)), hasL = 1;
      if (r1&1) ansR = (hasR?merge(query_help(--r1,l2,r2),ansR):query_help(--r1,l2,r2)), hasR = 1;
    }
    if (!hasL) return ansR; if (!hasR) return ansL;
    return merge(ansL,ansR);
  }
};