/*
 *Description:* Succint data structure to store strings in compressed space. It generalizes rank and select operations. Runs on $O(log sigma)$, where $sigma$ is the size of the alphabet
 *Status:* Tested
*/
template<typename T, int MAXLOG>
struct wavelet_tree {
  struct node {
    succinct_indexable_dictionary sid;
    node *ch[2];
    node() = default;
    node(size_t len) : sid(len + 1), ch{nullptr} {}
  };
  node *root;
  node *build(vector<T> &v, vector<T> &rbuff, int bit, int l, int r) {
    if (l >= r or bit == -1) return nullptr;
    node *_node = new node(r-l);
    ll left = 0, right = 0; 
    for (ll k = l; k < r; k++) {
      if ((v[k] >> bit) & 1)
        rbuff[right++] = v[k], _node->sid.set(k - l);
      else v[l + left++] = v[k];
    }
    for (int k = 0; k < right; k++) v[l + left + k] = rbuff[k];
    _node->sid.build();
    _node->ch[0] = build(v, rbuff, bit - 1, l, l + left);
    _node->ch[1] = build(v, rbuff, bit - 1, l + left, r);
    return _node;
  }
  wavelet_tree() = default;
  wavelet_tree(vector<T> &v) {
    vector<T> rbuff(v.size());
    root = build(v, rbuff, MAXLOG - 1, 0, v.size());
  }
  int rank(node *t, int l, int r, const T&x, int level) {
    if (l >= r or t == nullptr) return 0;
    if (level == -1) return r-l;
    bool f = (x >> level) & 1;
    l = t->sid.rank(f, l), r = t->sid.rank(f, r);
    return rank(t->ch[f], l, r, x, level-1);
  }
  int rank(const T &x, int r) { return rank(root, 0, r, x, MAXLOG-1); }
  T kth(node *t, int l, int r, int k, int level) {
    if (l >= r || t == nullptr) return 0;
    int cnt = t->sid.rank(false, r) - t->sid.rank(false, l);
    bool f = cnt <= k;
    l = t->sid.rank(f, l), r = t->sid.rank(f, r);
    if (f) return kth(t->ch[f], l, r, k - cnt, level - 1) | (T(1) << level);
    return kth(t->ch[f], l, r, k, level - 1);
  }
  // k-th(0-indexed) smallest number in v[l,r]
  T kth_smallest(int l, int r, int k) {
    return kth(root, l, r+1, k, MAXLOG - 1);
  }
  // k-th(0-indexed) largest number in v[l,r]
  T kth_largest(int l, int r, int k) {
    return kth(l, r, r - l - k);
  }
  int range_freq(node *t, int l, int r, T upper, int level) {
    if (t == nullptr || l >= r) return 0;
    bool f = ((upper >> level) & 1);
    int ret = 0;
    if (f) ret += t->sid.rank(false, r) - t->sid.rank(false, l);
    l = t->sid.rank(f, l), r = t->sid.rank(f, r);
    return range_freq(t->ch[f], l, r, upper, level - 1) + ret;
  }
  // count i s.t. (l <= i < r) && (v[i] < upper)
  int range_freq(int l, int r, T upper) {
    return range_freq(root, l, r, upper, MAXLOG - 1);
  }
};
