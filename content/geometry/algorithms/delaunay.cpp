/*
 *Description:* Delaunay Triangulation using divide and conquer with quad-edges. Each circumcircle contains none of the input points. If all points are collinear, `tri` is empty. Uses `__int128` for circumcircle test (coords up to $10^9$).
 *Time:* $O(n log n)$
 *Status:* Tested
 *Dependencies:* point2d
 */
template <typename T> struct delaunay {
  using pt = point2d<T>;
  using lll = __int128_t;
  struct Quad {
    Quad *rot, *o;
    pt p; int id; bool mark;
    pt& F() { return rot->rot->p; }
    int& Fi() { return rot->rot->id; }
    Quad*& r() { return rot->rot; }
    Quad* prev() { return rot->o->rot; }
    Quad* next() { return r()->prev(); }
  };
  Quad* pool;
  bool circ(pt p, pt a, pt b, pt c) {
    lll p2=p.norm(), A=a.norm()-p2, B=b.norm()-p2, C=c.norm()-p2;
    return p.cross(a,b)*C + p.cross(b,c)*A + p.cross(c,a)*B > 0;
  }
  Quad* makeEdge(pt orig, int oi, pt dest, int di) {
    auto nq = [&]() { return new Quad{nullptr,nullptr,{}, -1, false}; };
    Quad* r;
    if (pool) { r = pool; pool = r->o; }
    else { r = nq(); r->rot = nq(); r->rot->rot = nq(); r->rot->rot->rot = nq(); }
    r->r()->r() = r; r->rot->rot->rot->rot = r;
    pt arb{(T)1e18, (T)1e18};
    Quad* c = r;
    for (int i = 0; i < 4; i++) {
      c = c->rot; c->p = arb; c->id = -1;
      c->o = (i & 1) ? c : c->r();
    }
    r->p = orig; r->id = oi; r->F() = dest; r->Fi() = di;
    return r;
  }
  void splice(Quad* a, Quad* b) {
    swap(a->o->rot->o, b->o->rot->o); swap(a->o, b->o);
  }
  Quad* connect(Quad* a, Quad* b) {
    Quad* q = makeEdge(a->F(), a->Fi(), b->p, b->id);
    splice(q, a->next()); splice(q->r(), b); return q;
  }
  pair<Quad*,Quad*> rec(vector<pt>& s, vector<int>& ids, int lo, int hi) {
    int sz = hi - lo;
    if (sz <= 3) {
      Quad* a = makeEdge(s[lo],ids[lo], s[lo+1],ids[lo+1]);
      Quad* b = makeEdge(s[lo+1],ids[lo+1], s[lo+sz-1],ids[lo+sz-1]);
      if (sz == 2) return {a, a->r()};
      splice(a->r(), b);
      auto side = s[lo].cross(s[lo+1], s[lo+2]);
      Quad* c = side ? connect(b, a) : nullptr;
      return {side<0 ? c->r() : a, side<0 ? c : b->r()};
    }
    int mid = lo + sz/2;
    auto [ra, A] = rec(s, ids, lo, mid);
    auto [B, rb] = rec(s, ids, mid, hi);
    while ((B->p.cross(A->F(), A->p)<0 && (A=A->next())) ||
           (A->p.cross(B->F(), B->p)>0 && (B=B->r()->o)));
    Quad* base = connect(B->r(), A);
    if (A->p.x==ra->p.x && A->p.y==ra->p.y) ra = base->r();
    if (B->p.x==rb->p.x && B->p.y==rb->p.y) rb = base;
    auto valid = [&](Quad* e) { return e->F().cross(base->F(), base->p) > 0; };
    for (;;) {
      Quad* LC = base->r()->o;
      if (valid(LC)) while (circ(LC->o->F(), base->F(), base->p, LC->F()))
        { Quad* t=LC->o; splice(LC,LC->prev()); splice(LC->r(),LC->r()->prev()); LC->o=pool; pool=LC; LC=t; }
      Quad* RC = base->prev();
      if (valid(RC)) while (circ(RC->prev()->F(), base->F(), base->p, RC->F()))
        { Quad* t=RC->prev(); splice(RC,RC->prev()); splice(RC->r(),RC->r()->prev()); RC->o=pool; pool=RC; RC=t; }
      if (!valid(LC) && !valid(RC)) break;
      if (!valid(LC) || (valid(RC) && circ(RC->F(), base->F(), base->p, LC->F())))
        base = connect(RC, base->r());
      else base = connect(base->r(), LC->r());
    }
    return {ra, rb};
  }
  int n;
  vector<array<int, 3>> tri;
  delaunay() : pool(nullptr), n(0) {}
  delaunay(vector<T> &px, vector<T> &py) : pool(nullptr), n(0) { build(px, py); }
  void build(vector<T> &px, vector<T> &py) {
    n = (int)px.size(); tri.clear(); pool = nullptr;
    if (n < 2) return;
    vector<int> ord(n); iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
      return px[a]<px[b] || (px[a]==px[b] && py[a]<py[b]);
    });
    vector<pt> sp(n); vector<int> si(n);
    for (int i = 0; i < n; i++) { sp[i] = {px[ord[i]], py[ord[i]]}; si[i] = ord[i]; }
    Quad* e = rec(sp, si, 0, n).first;
    vector<Quad*> q = {e};
    int qi = 0;
    while (e->o->F().cross(e->F(), e->p) < 0) e = e->o;
    auto add = [&](Quad* e) {
      Quad* c = e; vector<int> face;
      do { c->mark=1; face.push_back(c->id); q.push_back(c->r()); c=c->next(); } while (c!=e);
      if ((int)face.size()==3) tri.push_back({face[0],face[1],face[2]});
    };
    add(e);
    while (qi < (int)q.size()) if (!(e=q[qi++])->mark) add(e);
  }
};