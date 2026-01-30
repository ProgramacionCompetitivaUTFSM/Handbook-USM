/*
 *Description:* Minkowski sum of two CONVEX polygons (handles degenerate)
 *Complexity:* $O(n + m)
$ */
template <typename T>
vector<Point2D<T>> minkowski(vector<Point2D<T>> &p, vector<Point2D<T>> &q) {
  vector<Point2D<T>> v;
  if (min(p.size(), q.size()) < 3) {
    for (auto &a : p) for (auto &b : q)
      v.push_back(a + b);
    return convexHull(v);
  }
  auto reorder = [](vector<Point2D<T>> &v) {
    if (((v[1] - v[0]) ^ (v[2] - v[0])) < 0)
      reverse(v.begin(), v.end());
    int pos = 0;
    for (int i = 1; i < (int)v.size(); i++)
      if (pair{v[i].y, v[i].x} < pair{v[pos].y, v[pos].x})
        pos = i;
    rotate(v.begin(), v.begin() + pos, v.end());
  };
  reorder(p), reorder(q);
  for (int i = 0; i < 2; i++)
    p.push_back(p[i]), q.push_back(q[i]);
  int i = 0, j = 0;
  while (i + 2 < p.size() or j + 2 < q.size()) {
    v.push_back(p[i] + q[j]);
    T c = (p[i + 1] - p[i]) ^ (q[j + 1] - q[j]);
    if (c >= 0 and i + 2 < p.size()) i++;
    if (c <= 0 and j + 2 < q.size()) j++;
  }
  return v;
}