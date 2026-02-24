/*
 *Description:* Signed distance from point $p$ to line through $a$, $b$. Positive on left side seen from $a$ to $b$. Uses point2d.
 *Status:* KACTL based, not self tested
*/
template<class T>
ld line_dist(point2d<T> a, point2d<T> b, point2d<T> p) {
  return (ld)((b-a)^(p-a)) / (b-a).abs();
}
