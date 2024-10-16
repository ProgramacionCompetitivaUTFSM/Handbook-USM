/*
 * Description: * Acts like an array, allowing us to reverse, sum, remove, slice, order of, and remove in $O(log n)$
 * Status: * Tested
 */
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
struct implicit_treap {
  static mt19937_64 MT;
  struct N {
    N *l, *r, *p; int s, pr, v; bool rv;
    N(int x): l(0), r(0), p(0), s(1), pr(MT()), v(x), rv(0) {}
  } *rt = 0;
  gp_hash_table<int, N*> mp; // Remove if TLE (this is for order_of)
  int sz(N *t) { return t ? t->s : 0; }
  void upd(N *t) {
    if (t->l) t->l->p = t;
    if (t->r) t->r->p = t;
    t->s = 1 + sz(t->l) + sz(t->r);
  }
  void push(N *t) {
    if (t && t->rv) {
      swap(t->l, t->r);
      if (t->l) t->l->rv ^= 1;
      if (t->r) t->r->rv ^= 1;
      t->rv = 0;
    }
  }
  void merge(N*& t, N* l, N* r) {
    push(l); push(r);
    if (!l || !r) t = l ? l : r;
    else if (l->pr > r->pr) merge(l->r, l->r, r), t = l;
    else merge(r->l, l, r->l), t = r;
    upd(t);
  }
  void split(N* t, int k, N*& l, N*& r) {
    if (!t) { l = r = 0; return; }
    push(t);
    if (sz(t->l) < k) split(t->r, k - sz(t->l) - 1, t->r, r), l = t;
    else split(t->l, k, l, t->l), r = t;
    upd(t);
  }
  void flip(int l, int r) {
    N *a, *b, *c;
    split(rt, l, a, b), split(b, r - l + 1, b, c);
    b->rv ^= 1;
    merge(rt, a, b), merge(rt, rt, c);
  }
  void push_back(int x) {
    N* n = new N(x);
    mp[x] = n, merge(rt, rt, n);
  }
  int order_of(int x) {
    N* t = mp[x];
    vector<N*> path;
    for (N* cur = t; cur; cur = cur->p)
      path.push_back(cur);
    reverse(path.begin(), path.end());
    for (N* n : path) push(n), upd(n);
    int idx = sz(t->l);
    N* cur = t;
    while (cur->p) {
      if (cur == cur->p->r)
        idx += sz(cur->p->l) + 1;
      cur = cur->p;
    }
    return idx;
  }
};
mt19937_64 implicit_treap::MT(chrono::system_clock::now().time_since_epoch().count());
