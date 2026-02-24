/*
 *Description:* Shortest distance from point $p$ to segment $s$-$e$. Uses point2d.
 *Status:* KACTL based, not self tested
*/
using P = point2d<ld>;
ld seg_dist(P s, P e, P p) {
  if (s.sqdist(e) < 1e-18) return (p-s).abs();
  auto d = (e-s).norm();
  auto t = min(d, max((ld)0.0, (p-s)|(e-s)));
  return ((p-s)*d - (e-s)*t).abs() / d;
}
