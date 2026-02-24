/*
 *Description:* Check if a point is inside, bounds or out of the polygon
 - 0: Bounds
 - 1: Inside
 - -1: Out
 *Status:* Tested
*/
template<typename T>
int point_inside_polygon(vector<point2d<T>> &P, point2d<T> q) {
  int N = P.size(), cnt = 0;
  for(int i = 0; i < N; i++) {
    int j = (i == N-1 ? 0 : i+1);
    segment<T> s(P[i], P[j]);
    if(s.contain(q)) return 0;
    if(P[i].x <= q.x and q.x < P[j].x and q.cross(P[i], P[j]) < 0) cnt++;
    else if(P[j].x <= q.x and q.x < P[i].x and q.cross(P[j], P[i]) < 0) cnt++;
  }
  return cnt&1 ? 1 : -1;
}