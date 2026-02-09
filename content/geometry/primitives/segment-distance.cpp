/*
 *Description:* Shortest distance from point $p$ to segment $s$-$e$. Uses Point2D.
 *Status:* KACTL based, not self tested
*/
using P = Point2D<ld>;
ld segDist(P s, P e, P p) {
  if (s.sqdist(e) < 1e-18) return (p-s).abs();
  auto d = (e-s).norm();
  auto t = min(d, max(0.0, (p-s)|(e-s)));
  return ((p-s)*d - (e-s)*t).abs() / d;
}
