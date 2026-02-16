/*
 *Description:* External tangents of two circles (negate $r_2$ for internal). Returns 0, 1 or 2 tangents. `.first`/`.second` = tangency points on circle 1/2. Set $r_2 = 0$ for point tangents. Uses point2d.
 *Status:* KACTL based, not self tested
*/
using P = point2d<ld>;
vector<pair<P,P>> tangents(P c1, ld r1,
    P c2, ld r2) {
  P d = c2 - c1;
  ld dr = r1 - r2, d2 = d.norm(), h2 = d2 - dr*dr;
  if (d2 < 1e-18 || h2 < 0) return {};
  vector<pair<P,P>> out;
  P perp = {-d.y, d.x};
  for (ld sign : {-1.0, 1.0}) {
    P v = (d*dr + perp*sqrt(h2)*sign) / d2;
    out.push_back({c1 + v*r1, c2 + v*r2});
  }
  if (h2 < 1e-18) out.pop_back();
  return out;
}
