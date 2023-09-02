struct treap {
  static mt19937_64 MT;
  struct node {
    node *left, *right; ll key, priority, value, max_value;
    node(ll k, ll v = 0) {
      left = right = NULL; key = k; priority = MT(); 
      max_value = value = v;
    }
  };
  ll value(node* T) { return T ? T->value : -INF; }
  ll max_value(node* T) { return T ? T->max_value : -INF; }
  void update(node* T) { 
    T->max_value = max({T->value, max_value(T->left), max_value(T->right)});}
  node *root;
  void merge(node* &T, node* T1, node* T2) {
    if(T1 == NULL) { T = T2; return; }
    if(T2 == NULL) { T = T1; return; }
    if(T1->priority > T2->priority)
      merge(T1->right, T1->right, T2), T = T1;
    else merge(T2->left, T1, T2->left), T = T2;
    return update(T);
  }
  void merge(node* &T, node* T1, node* T2, node* T3) {
    merge(T, T1, T2); merge(T, T, T3);
  }
  void split(node* T, ll x, node* &T1, node* &T2) {
    if(T == NULL) { T1 = T2 = NULL; return; }
    if(T->key <= x) { split(T->right, x, T->right, T2); T1 = T; } 
    else { split(T->left, x, T1, T->left); T2 = T; }
    return update(T);
  }
  void split(node* T, ll x, ll y, node* &T1, node* &T2, node* &T3) {
    split(T, x-1, T1, T2);  split(T2, y, T2, T3);
  }
  bool search(node* T, ll x) {
    if(T == NULL) return false; if(T->key == x) return true;
    if(x < T->key) return search(T->left, x);
    return search(T->right, x);
  }
  void insert(node* &T, node* n) {
    if(T == NULL) { T = n; return; }
    if(n->priority > T->priority) {
      split(T, n->key, n->left, n->right); T = n;
    } else if(n->key < T->key) insert(T->left, n);
    else insert(T->right, n);
    return update(T);
  }
  void erase(node* &T, ll x) {
    if(T == NULL) return;
    if(T->key == x) { merge(T, T->left, T->right); }
    else if(x < T->key) erase(T->left, x);
    else erase(T->right, x);
    return update(T);
  }
  bool set(node* T, ll k, ll v) {
    if(T == NULL) return false;
    bool found;
    if(T->key == k) T->value = k, found = true;
    else if(k < T->key) found = set(T->left, k, v);
    else found = set(T->right, k, v);
    if(found) update(T); return found;
  }
  node* find(node* T, ll k) {
    if(T == NULL) return NULL;
    if(T->key == k) return T;
    if(k < T->key) return find(T->left, k);
    return find(T->right, k);
  }
  treap() {root = NULL;}
  treap(ll x) {root = new node(x);}
  treap &merge(treap &O) {merge(root, root, O.root); return *this; }
  treap split(ll x) {treap ans; split(root, x, root, ans.root); return ans; }
  bool search(ll x) {return search(root, x); }
  void insert(ll x) {if(search(root, x)) return; return insert(root, new node(x));}
  void erase(ll x) {return erase(root, x); }
  void set(ll k, ll v) {if(set(root, k, v)) return; insert(root, new node(k, v));}
  ll operator[](ll k) {
    node* n = find(root, k);
    if(n == NULL) n = new node(k), insert(root, n); return n->value;
  }
  ll query(ll a, ll b) {
    node *T1, *T2, *T3; split(root, a, b, T1, T2, T3);
    ll ans = max_value(T2); merge(root, T1, T2, T3);
    return ans;
  }
};
mt19937_64 treap::MT(chrono::system_clock::now().time_since_epoch().count());
