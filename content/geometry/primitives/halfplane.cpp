/*
 *Description:* Halfplane
 *Status:* Partially tested
*/
struct halfplane {
  point2d<ld> p, pq;
  ld angle;
  halfplane() {}
  halfplane(point2d<ld> &a, point2d<ld> &b) : p(a), pq(b - a) {
    angle = atan2l(pq.y, pq.x);
  }
  bool out(point2d<ld> r) { return ((pq) ^ (r - p)) < -eps; }
  bool operator<(halfplane &e) { return angle < e.angle; }
  friend point2d<ld> inter(halfplane &s, halfplane &t) {
    ld alpha = ((t.p - s.p) ^ t.pq) / ((s.pq) ^ (t.pq));
    return s.p + (s.pq * alpha);
  }
};
