/*
 *Description:* Area of intersection of a circle (center $c$, radius $r$) with a CCW polygon. $O(n)$. Uses Point2D.
 *Status:* KACTL based, not self tested
*/
using P = Point2D<ld>;
ld circlePoly(P c, ld r, vector<P>& ps) {
  auto arg = [](P p, P q) {
    return atan2(p^q, p|q);
  };
  auto tri = [&](P p, P q) {
    auto r2 = r*r/2;
    P d = q - p;
    auto a = (d|p)/d.norm(), b = (p.norm()-r*r)/d.norm();
    auto det = a*a - b;
    if (det <= 0) return arg(p,q) * r2;
    auto s = max(0.0, -a-sqrt(det));
    auto t = min(1.0, -a+sqrt(det));
    if (t < 0 || 1 <= s) return arg(p,q) * r2;
    P u = p + d*s, v = q + d*(t-1);
    return arg(p,u)*r2 + (u^v)/2 + arg(v,q)*r2;
  };
  ld sum = 0;
  int n = ps.size();
  for (int i = 0; i < n; i++)
    sum += tri(ps[i]-c, ps[(i+1)%n]-c);
  return sum;
}
