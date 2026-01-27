/*
 *Description:* 2D circle, constructors: empty, (center, radius), (a, b, c)
 * circumcircle Status:* Tested
 */
template <typename T> struct circle {
  Point2D<T> c;
  T r;
  circle() : c(), r(0) {}
  circle(Point2D<T> c_, T r_) : c(c_), r(r_) {}
  circle(Point2D<T> a, Point2D<T> b, Point2D<T> p) {
    Point2D<T> ab = b - a, ap = p - a;
    T d = 2 * (ab ^ ap);
    if (sign(d) == 0) {
      c = Point2D<T>();
      r = 0;
      return;
    }
    T s = ab.norm(), t = ap.norm();
    c = a + Point2D<T>(ap.y * s - ab.y * t, ab.x * t - ap.x * s) / d;
    r = c.sqdist(a);
    r = sqrtl(r);
  }
};