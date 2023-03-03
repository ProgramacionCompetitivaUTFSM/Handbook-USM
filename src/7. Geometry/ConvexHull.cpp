// Monotone chain Convex Hull
template <typename T>
vector<Point2D<T>> convexHull(vector<Point2D<T>> &P, bool collinear = 1) {
  int N = P.size(), k = 0;
  sort(P.begin(), P.end(), [](const Point2D<T> &p1, const Point2D<T> &p2) {
    if (p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
  });
  vector<Point2D<int>> H(2*N);
  // Build lower hull
  for(int i = 0; i < N; ++i) {
    while(collinear and k >= 2 and H[k-2].cross(H[k-1], P[i]) < 0) k--;
    while(!collinear and k >= 2 and H[k-2].cross(H[k-1], P[i]) <= 0) k--;
    H[k++] = P[i];
  }
  // Build upper hull
  for(int i = N-1, t = k+1; i > 0; --i) {
    while(collinear and k >= t and H[k-2].cross(H[k-1], P[i-1]) < 0) k--;
    while(!collinear and k >= t and H[k-2].cross(H[k-1], P[i-1]) <= 0) k--;
    H[k++] = P[i-1];
  }
  // k para agregar primer punto al final
  H.resize(k-1);
  return H;
}
