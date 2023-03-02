template<typename T >
struct Segment {
  Point2D< T > P;
  Point2D< T > Q;
  Segment(Point2D<T> P, Point2D<T> Q): P(P), Q(Q) {}
  int sign(T x, T eps = 0) { return x > eps ? 1 : x < -eps ? -1 : 0; }
  bool contain(Point2D<T> p, T eps = 0) {
    return (P - p).dot(Q - p) <= (T)0 and abs((Q - P).cross(p - P)) <= eps;
  }
  bool intersect(Segment<T> b) {
    if (this->contain(b.P) or this->contain(b.Q) or b.contain(P) or b.contain(Q))
        return true;
    // change < 0 or <= depending the problem
    return sign( ((b.P) - P).cross(Q - P) )*sign( (b.Q - P).cross(Q - P) ) < 0 and
           sign((P - b.Q).cross(b.Q - b.P))*sign( (Q- b.P).cross(b.Q - b.P) ) < 0;
  }
};
