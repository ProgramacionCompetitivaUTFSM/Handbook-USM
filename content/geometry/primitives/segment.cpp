/*
 *Description:* Segment implementation
 *Status:* Partially tested
*/
template<typename T >
struct Segment {
  Point2D< T > P;
  Point2D< T > Q;
  const T INF = numeric_limits<T>::max();
  Segment(Point2D<T> P, Point2D<T> Q): P(P), Q(Q) {}
  int sign(T x, T eps = 0) { return x > eps ? 1 : x < -eps ? -1 : 0; }
  bool contain(Point2D<T> p, T eps = 0) {
    return ((P - p)|(Q - p)) <= (T)0 and abs(((Q - P)^(p - P))) <= eps;
  }
  bool intersect(Segment<T> b) {
    if (this->contain(b.P) or this->contain(b.Q) or b.contain(P) or b.contain(Q))
        return true;
    // change < 0 or <= depending the problem
    return sign((((b.P) - P))^((Q - P)))*sign(((b.Q - P)^(Q - P))) < 0 and
           sign(((P - b.Q)^(b.Q - b.P)))*sign(((Q- b.P)^(b.Q - b.P))) < 0;
  }
  // not tested
  Point2D<T> intersection(Segment<T> b) {
    if(this->intersect(b))
      return (((b.Q-b.P)^(Q-b.P))*P + ((P-b.P)^(b.Q-b.P))*Q)/((P-Q)^(b.Q-b.P));
    return {INF, INF};
  }
};