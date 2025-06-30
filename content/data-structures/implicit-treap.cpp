/*
 *Description:* Acts like an array, allowing us to reverse, sum, remove, slice, order of, and remove in $O(log n)$
 *Status:* Tested
 */
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct implicit_treap {
  static mt19937_64 MT;
  struct node{
    node *l = nullptr, *r = nullptr, *par = nullptr;
    ll sz = 1, p = MT(), v, sumv, lzsum = 0;
    bool lzflip = false;
    node(ll x=0) { sumv=v=x; }
  } *root = nullptr;
  gp_hash_table<int, node*> mp; // Mapping values to nodes for order_of
  implicit_treap(){root=nullptr;}
  implicit_treap(ll x){root=new node(x);}
  ll sz(node* T) { return T?T->sz:0; }
  ll sumv(node* T) { return T?T->sumv:0;};
  void upd(node* T){
    if (T->l) T->l->par = T;
    if (T->r) T->r->par = T;
    T->sumv=T->v+sumv(T->l)+sumv(T->r);
    T->sz=1+sz(T->l)+sz(T->r);
  }
  void push(node* T){
    if(T->lzsum){
      T->v+=T->lzsum;
      T->sumv+=T->sz*T->lzsum;
      if(T->l)T->l->lzsum+=T->lzsum;
      if(T->r)T->r->lzsum+=T->lzsum;
      T->lzsum=0;
    }
    if(T->lzflip){
      swap(T->l,T->r);
      if(T->l)T->l->lzflip^=1;
      if(T->r)T->r->lzflip^=1;
      T->lzflip=0;
    }
  }
  void merge(node*& T,node* L,node* R){
    if(!L||!R){T=L?L:R;return;}
    push(L);push(R);
    if(L->p>R->p) merge(L->r,L->r,R), T=L;
    else merge(R->l,L,R->l), T=R;
    upd(T);
  }
  void split(node* T,int k,node*& L,node*& R){
    if(!T){L=R=nullptr;return;}
    push(T);
    int key=sz(T->l);
    if(key<=k) split(T->r,k-key-1,T->r,R), L=T;
    else split(T->l,k,L,T->l), R=T;
    upd(T);
  }
  void set(node* T,int k,ll x){
    push(T);
    int key=sz(T->l);
    if(key==k)T->v=x;
    else if(k<key)set(T->l,k,x);
    else set(T->r,k-key-1,x);
    upd(T);
  }
  node* find(node* T,int k){
    push(T);
    int key=sz(T->l);
    if(key==k) return T;
    if(k<key) return find(T->l,k);
    return find(T->r,k-key-1);
  }
  int size(){return sz(root);}
  implicit_treap& merge(implicit_treap& O){
    merge(root,root,O.root);
    return *this;
  }
  implicit_treap split(int k){
    implicit_treap ans;
    split(root,k,root,ans.root);
    return ans;
  }
  void erase(int i,int j){
    node *T1,*T2,*T3;
    split(root,i-1,T1,T2), split(T2,j-i,T2,T3);
    merge(root,T1,T3);
  }
  void erase(int k){erase(k,k);}
  void set(int k,ll x){set(root,k,x);}
  ll operator[](int k){return find(root,k)->v;}
  ll query(int i,int j){
    node *T1,*T2,*T3;
    split(root,i-1,T1,T2), split(T2,j-i,T2,T3);
    ll ans=sumv(T2);
    merge(T2,T2,T3), merge(root,T1,T2);
    return ans;
  }
  void update(int i,int j,ll x){
    node *T1,*T2,*T3;
    split(root,i-1,T1,T2), split(T2,j-i,T2,T3);
    T2->lzsum+=x;
    merge(T2,T2,T3), merge(root,T1,T2);
  }
  void flip(int i,int j){
    node *T1,*T2,*T3;
    split(root,i-1,T1,T2), split(T2,j-i,T2,T3);
    T2->lzflip^=1;
    merge(T2,T2,T3), merge(root,T1,T2);
  }
  void insert(int i,ll x){
    node *T1,*T2;
    split(root,i-1,T1,T2);
    merge(T1,T1,new node(x)), merge(root,T1,T2);
  }
  void push_back(ll x){auto nn = new node(x); merge(root,root, nn); mp[x] = nn;}
  int order_of(int x) {
    node* t = mp[x];
    vector<node*> path;
    for (node* cur = t; cur; cur = cur->par)
      path.push_back(cur);
    reverse(path.begin(), path.end());
    for (node* n : path) push(n), upd(n);
    int idx = sz(t->l);
    node* cur = t;
    while (cur->par) {
      if (cur == cur->par->r)
        idx += sz(cur->par->l) + 1;
      cur = cur->par;
    }
    return idx;
  }
};
mt19937_64 implicit_treap::MT(chrono::system_clock::now().time_since_epoch().count());
