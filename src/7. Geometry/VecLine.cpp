template< T >
struct Line {
  Point2D< T > a;
  Point2D< T > d;
  Line() {}
  Line(Point2D< T > a_, Point2D< T > d_) {
    a = a_; d = d_;
  }
  Line(Point2D< T > p1, Point2D< T > p2) {
    // TO DO
  }
  Point2D< T > intersect(Line< T > l) {
    Point2D a2a1 = l.a - a;
    return a + a2a1.cross(l.d) / d.cross(l.d) * d;
  }
};
