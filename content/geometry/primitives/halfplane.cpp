/*
 *Description:* Halfplane
 *Status:* Partially tested
*/
struct Halfplane {
  Point2D<ld> p, pq;
  ld angle;
  Halfplane() {}
  Halfplane(Point2D<ld> &a, Point2D<ld> &b) : p(a), pq(b - a) {
    angle = atan2l(pq.y, pq.x);
  }
  bool out(Point2D<ld> r) { return ((pq) ^ (r - p)) < -eps; }
  bool operator<(Halfplane &e) { return angle < e.angle; }
  friend Point2D<ld> inter(Halfplane &s, Halfplane &t) {
    ld alpha = ((t.p - s.p) ^ t.pq) / ((s.pq) ^ (t.pq));
    return s.p + (s.pq * alpha);
  }
};
