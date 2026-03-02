/*
 *Description:* Delaunay Triangulation via lifting to paraboloid $z = x^2 + y^2$. Exact integer arithmetic. `degenerate=true` if all points are collinear.
 *Time:* $O(n log n)$ expected
 *Status:* Tested
 *Dependencies:* point3d, convex_hull_3d
 */
template <typename T> struct delaunay : convex_hull_3d<T> {
  using pt = point3d<T>;
  int n;
  vector<array<int, 3>> tri;

  delaunay() : n(0) {}
  delaunay(vector<T> &px, vector<T> &py) : n(0) { build(px, py); }

  void build(vector<T> &px, vector<T> &py) {
    n = (int)px.size();
    tri.clear();
    if (n < 3) return;
    vector<pt> lifted(n);
    for (int i = 0; i < n; i++)
      lifted[i] = {px[i], py[i], px[i] * px[i] + py[i] * py[i]};
    this->p = move(lifted);
    this->build_hull();
    if (this->degenerate) return;
    map<pair<T, T>, int> idx;
    for (int i = 0; i < n; i++) idx[{px[i], py[i]}] = i;
    int hn = (int)this->p.size();
    vector<int> re(hn);
    for (int i = 0; i < hn; i++)
      re[i] = idx[{this->p[i].x, this->p[i].y}];
    for (auto &f : this->faces()) {
      pt nm = (this->p[f[1]] - this->p[f[0]]) ^ (this->p[f[2]] - this->p[f[0]]);
      if (nm.z < 0)
        tri.push_back({re[f[0]], re[f[2]], re[f[1]]});
    }
  }
};