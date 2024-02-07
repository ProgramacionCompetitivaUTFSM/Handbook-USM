struct implicit_treap {
  static mt19937_64 MT;
  struct node { node *left, *right;
    int sz, priority, value, sum_value, lazy_sum, lazy_flip;
    node(ll v = 0) {
      left = right = NULL; priority = MT(); lazy_flip = false;
      sz = 1; lazy_sum = 0; sum_value = value = v; } };
  ll value(node* T) { return T ? T->value : 0; }
  ll sum_value(node* T) { return T ? T->sum_value : 0; }
  int sz(node* T) { return T ? T->sz : 0; }
  int key(node* T) { return sz(T->left); }
  void update(node* T) {
    T->sum_value =  T->value + sum_value(T->left) + sum_value(T->right);
    T->sz = 1 + sz(T->left) + sz(T->right);
  }
  void sum_push(node* T) {
    if(T->lazy_sum) {
      T->value += T->lazy_sum; T->sum_value += T->sz*T->lazy_sum;
      if(T->left) T->left->lazy_sum += T->lazy_sum;
      if(T->right) T->right->lazy_sum += T->lazy_sum;
    } T->lazy_sum = 0;
  }
  void flip_push(node* T) {
    if(T->lazy_flip) {
      swap(T->left, T->right);
      if(T->left) T->left->lazy_flip = !T->left->lazy_flip;
      if(T->right) T->right->lazy_flip = !T->right->lazy_flip;
    } T->lazy_flip = false;
  } node *root;
  void push(node* T) { sum_push(T);flip_push(T); }
  void merge(node* &T, node* T1, node* T2) {
    if(T1 == NULL) {T = T2; return;} if(T2 == NULL) { T = T1; return; }
    push(T1); push(T2);
    if(T1->priority > T2->priority) merge(T1->right, T1->right, T2), T = T1;
    else merge(T2->left, T1, T2->left), T = T2; return update(T);
  }
  void merge(node* &T,node* T1,node* T2,node* T3) {merge(T, T1, T2); merge(T, T, T3);}
  void split(node* T, int k, node* &T1, node* &T2) {
    if(T == NULL) { T1 = T2 = NULL; return; } push(T);
    if(key(T) <= k) { split(T->right, k - (key(T)+1), T->right, T2); T1 = T;
    } else split(T->left, k, T1, T->left), T2 = T; return update(T);
  }
  void split(node* T, int i, int j, node* &T1, node* &T2, node* &T3) {
    split(T, i-1, T1, T2);  split(T2, j-i, T2, T3); }
  void set(node* T, int k, ll v) {
    push(T); if(key(T) == k) T->value = v;
    else if(k < key(T)) set(T->left, k, v);
    else set(T->right, k - (key(T)+1), v);
    return update(T); }
  node* find(node* T, int k) {
    push(T); if(key(T) == k) return T;
    if(k < key(T)) return find(T->left, k);
    return find(T->right, k - (key(T)+1)); }
  implicit_treap() { root = NULL; }
  implicit_treap(ll x) { root = new node(x); }
  int size() { return sz(root); }
  implicit_treap &merge(implicit_treap &O){ merge(root, root, O.root); return *this;}
  implicit_treap split(int k) {
    implicit_treap ans; split(root, k, root, ans.root); return ans;
  }
  void erase(int i, int j){
    node *T1, *T2, *T3; split(root, i, j, T1, T2, T3); merge(root, T1, T3);
  }
  void erase(int k) { return erase(k, k); }
  void set(int k, ll v) { set(root, k, v); }
  ll operator[](int k) { return find(root, k)->value; }
  ll query(int i, int j) {
    node *T1, *T2, *T3; split(root, i, j, T1, T2, T3);
    ll ans = sum_value(T2); merge(root, T1, T2, T3);
    return ans;
  }
  void update(int i, int j, ll x) {
    node *T1, *T2, *T3; split(root, i, j, T1, T2, T3);
    T2->lazy_sum += x; merge(root, T1, T2, T3);
  }
  void flip(int i, int j) {
    node *T1, *T2, *T3; split(root, i, j, T1, T2, T3);
    T2->lazy_flip = !T2->lazy_flip; merge(root, T1, T2, T3);
  }
  void insert(int i, ll x) {
    node* T; split(root, i-1, root, T); merge(root, root, new node(x), T); }
  void push_back(ll x) { merge(root, root, new node(x)); }
  void push_front(ll x) { merge(root, new node(x), root); }
};
mt19937_64 implicit_treap::MT(chrono::system_clock::now().time_since_epoch().count());