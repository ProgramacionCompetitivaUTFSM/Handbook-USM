template< T >
struct Segment {
  // Segment (P, Q)
  Point2D< T > P;
  Point2D< T > Q;
  Segment(Point2D< T > P_, Point2D< T > Q_) {
    P = P_;
    Q = Q_;
  }
  bool check(T a, T b, T c, T d) {
    if(a > b) swap(a, b);
    if(c > d) swap(c, d);
    return max(a, c) <= min(b, d);
  }
  int sign(T x) { return x > 0 ? 1 : (x < 0 : -1 : 0); } 
  bool intersect(Segment< T > S) {
    if((P - S.P).cross(S.Q - S.P) == 0 && (Q - S.P).cross(S.Q - S.P) == 0) {
      return check(P.x, Q.x, S.P.x, S.Q.x) && check(P.y, Q.y, S.P.y, S.Q.y);
    }
    return sign((Q - P).cross(S.P - P)) != sign((Q - P).cross(S.Q - P)) &&
    sign((S.Q - S.P).cross(P - S.P)) != sign((S.Q - S.P).cross(Q - S.P));
  }
};
