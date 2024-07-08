/*
 *Descripcion:* Check if a point is inside, bounds or out of the polygon
 - 0: Bounds
 - 1: Inside
 - 2: Out
 *Status:* Tested
*/
template<typename T>
int pointInsidePolygon(vector<Point2D<T>> &P, Point2D<T> q) {
  int N = P.size(), cnt = 0;
  for(int i = 0; i < N; i++) {
    int j = (i == N-1 ? 0 : i+1);
    Segment<T> s(P[i], P[j]);
    if(s.contain(q)) return 0;
    if(P[i].x <= q.x and q.x < P[j].x and q.cross(P[i], P[j]) < 0) cnt++;
    else if(P[j].x <= q.x and q.x < P[i].x and q.cross(P[j], P[i]) < 0) cnt++;
  }
  return cnt&1 ? 1 : -1;
}