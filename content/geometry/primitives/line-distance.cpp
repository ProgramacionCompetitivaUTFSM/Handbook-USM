/*
 *Description:* Signed distance from point $p$ to line through $a$, $b$. Positive on left side seen from $a$ to $b$. Uses Point2D.
 *Status:* KACTL based, not self tested
*/
template<class T>
ld lineDist(Point2D<T> a, Point2D<T> b, Point2D<T> p) {
  return (ld)((b-a)^(p-a)) / (b-a).abs();
}
