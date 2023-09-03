template<typename T>
vector<Point2D<T>> convexHull(vector<Point2D<T>> cloud, bool ac = 0) {
  int n = cloud.size(), k = 0;
  sort(cloud.begin(), cloud.end(), [](Point2D<T> &a, Point2D<T> &b) {
    return a.x < b.x or (a.x == b.x and a.y < b.y);
  });
  if (n <= 2 or (ac and n <= 3)) return cloud;
  bool allCollinear = true;
  for (int i = 2; i < n; ++i) {
    if (((cloud[1] - cloud[0]) ^ (cloud[i] - cloud[0])) != 0) {
      allCollinear = false; break;
    }
  }
  if (allCollinear) return cloud;
  vector<Point2D<T>> ch(2 * n);
  auto process = [&](int st, int end, int stp, int t, auto cmp) {
    for (int i = st; i != end; i += stp) {
      while (k >= t and cmp(ch[k - 1], ch[k - 2], cloud[i])) k--;
      ch[k++] = cloud[i];
    }
  };
  process(0, n, 1, 2, [&](auto a, auto b, auto c) {
    return ((a - b) ^ (c - b)) < 0;
  });
  process(n - 2, -1, -1, k + 1, [&](auto a, auto b, auto c) {
    return ((a - b) ^ (c - b)) < (ac ? 0 : 1);
  });
  ch.resize(k - 1);
  return ch;
}
