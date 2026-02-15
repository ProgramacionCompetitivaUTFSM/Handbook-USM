/*
 *Description:* 2D circle, constructors: empty, (center, radius), (a, b, c)
 * circumcircle Status:* Tested
 */
template <typename T> struct circle {
  point2d<T> c;
  T r;
  circle() : c(), r(0) {}
  circle(point2d<T> c_, T r_) : c(c_), r(r_) {}
  circle(point2d<T> a, point2d<T> b, point2d<T> p) {
    point2d<T> ab = b - a, ap = p - a;
    T d = 2 * (ab ^ ap);
    if (sign(d) == 0) {
      c = point2d<T>();
      r = 0;
      return;
    }
    T s = ab.norm(), t = ap.norm();
    c = a + point2d<T>(ap.y * s - ab.y * t, ab.x * t - ap.x * s) / d;
    r = c.sqdist(a);
    r = sqrtl(r);
  }
};