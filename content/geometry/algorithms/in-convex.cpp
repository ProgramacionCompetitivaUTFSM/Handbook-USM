/*
 *Description:* Point inside convex polygon (CCW, lowest-leftmost first)
 *Returns:* 1 inside, 0 border, -1 outside
 *Complexity:* $O(log n)$
 */
template <typename T> int in_convex(vector<point2d<T>> &P, point2d<T> q) {
  int n = P.size();
  if (n < 3) return -1;
  point2d<T> q0 = q - P[0];
  T c1 = (P[1] - P[0]) ^ q0, c2 = (P[n - 1] - P[0]) ^ q0;
  if (c1 < 0 || c2 > 0) return -1;
  int l = 1, r = n - 1;
  while (r - l > 1) {
    int mid = (l + r) / 2;
    ((P[mid] - P[0]) ^ q0) >= 0 ? l = mid : r = mid;
  }
  T c = (P[l + 1] - P[l]) ^ (q - P[l]);
  return c < 0 ? -1 : (c == 0 || c1 == 0 || c2 == 0 ? 0 : 1);
}