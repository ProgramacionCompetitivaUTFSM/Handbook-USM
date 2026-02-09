/*
 *Description:* Returns the centroid (center of mass) of a polygon. $O(n)$. Uses Point2D.
 *Status:* KACTL based, not self tested
*/
using P = Point2D<ld>;
P polygonCenter(vector<P>& v) {
  P res(0, 0); ld A = 0;
  int n = v.size();
  for (int i = 0, j = n-1; i < n; j = i++) {
    res = res + (v[i]+v[j]) * (v[j]^v[i]);
    A += v[j]^v[i];
  }
  return res / A / 3;
}
