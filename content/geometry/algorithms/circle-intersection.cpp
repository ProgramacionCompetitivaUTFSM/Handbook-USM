/*
 *Description:* Computes the pair of points where two circles intersect. Returns false if no intersection. Uses point2d.
 *Status:* KACTL based, not self tested
*/
using P = point2d<ld>;
bool circle_inter(P a, P b, ld r1, ld r2,
    pair<P,P>* out) {
  if (a.sqdist(b) < 1e-18) return false;
  P vec = b - a;
  ld d2 = vec.norm(), sum = r1+r2, dif = r1-r2,
    p = (d2 + r1*r1 - r2*r2) / (d2*2),
    h2 = r1*r1 - p*p*d2;
  if (sum*sum < d2 || dif*dif > d2) return false;
  P per = {-vec.y, vec.x};
  P mid = a + vec*p;
  per = per * sqrt(fmax(0, h2) / d2);
  *out = {mid + per, mid - per};
  return true;
}
