/*
 *Description:* Returns polygon with everything to the left of line $s -> e$ cut away. Uses point2d.
 *Status:* KACTL based, not self tested
*/
using P = point2d<ld>;
vector<P> polygon_cut(vector<P>& poly, P s, P e) {
  vector<P> res;
  int n = poly.size();
  for (int i = 0; i < n; i++) {
    P cur = poly[i], prev = i ? poly[i-1] : poly.back();
    auto a = s.cross(e, cur), b = s.cross(e, prev);
    if ((a < 0) != (b < 0))
      res.push_back(cur + (prev-cur) * (a / (a-b)));
    if (a < 0) res.push_back(cur);
  }
  return res;
}
