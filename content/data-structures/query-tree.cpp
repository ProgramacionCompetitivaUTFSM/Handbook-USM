struct query{
  int v,u;
  bool status;
  query(int _v,int _u) : v(_v),u(_u) {};
};
struct query_tree{
  vector<vector<query>> tree;
  int size;
  // rollback structure
  UnionFindRB uf;
  query_tree(int _size,int n) : size(_size) {uf = UnionFindRB(n); tree.resize(4*_size + 4);}
  void addTree(int v,int l,int r,int ul,int ur, query& q){
    if(ul > ur) return;
    if(l == ul && ur == r){tree[v].push_back(q); return; }
    int mid = (l + r)/2;
    addTree(2*v,l,mid,ul,min(ur,mid),q);
    addTree(2*v + 1,mid + 1,r,max(ul,mid + 1),ur,q);
  }
  void add(query q,int l,int r){addTree(1,0,size - 1,l,r,q);}
  void dfs(int v,int l,int r,vector<int> &ans){
    // change in data structure
    for(query &q: tree[v]) q.status = uf.unionSet(q.v,q.u);
    if(l == r) ans[l] = uf.comps;
    else{
      int mid = (l + r)/2;
      dfs(2*v,l,mid,ans);
      dfs(2*v + 1,mid + 1,r,ans);
    }
    // rollback in data structure
    for(query q: tree[v]) if(q.status) uf.rb();
  }
  vector<int> getAns(){
    vector<int> ans(size);
    dfs(1,0,size - 1,ans);
    return ans;
  }
};