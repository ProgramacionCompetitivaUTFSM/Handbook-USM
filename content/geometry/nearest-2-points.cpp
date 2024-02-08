/*
 *Description:* Using divide and conquer, allow us to know what are the two nearest point between them
 *Status:* Tested on CSES
*/
#define sq(x) ((x)*(x))
template <typename T>
pair<Point2D<T>, Point2D<T>> nearestPoints(vector<Point2D<T>> &P, int l, int r) {
  const T INF = 1e10;
  if (r-l == 1) return {P[l], P[r]};
  if (l >= r) return {{INF, INF}, {-INF, -INF}};
 
  int m = (l+r)/2;
  pair<Point2D<T>, Point2D<T>> D1, D2, D;
  D1 = nearestPoints(P, l, m);
  D2 = nearestPoints(P, m+1, r);
  D = (D1.first.sqdist(D1.second) <= D2.first.sqdist(D2.second) ? D1 : D2);
 
  T d = D.first.sqdist(D.second), x_center = (P[m].x + P[m+1].x)/2;
  vector<Point2D<T>> Pk;
  for (int i = l; i <= r; i++)
    if (sq(P[i].x-x_center) <= d)
      Pk.push_back(P[i]);
 
  sort(Pk.begin(), Pk.end(), [](const Point2D<T> p1, const Point2D<T> p2) {
    return p1.y != p2.y ? p1.y < p2.y : p1.x < p2.x;
  });
  
  for(int i = 0; i < Pk.size(); ++i) {
    for(int j = i-1; j >= 0; --j) {
      if(sq(Pk[i].y-Pk[j].y) > d) break;
      if(Pk[i].sqdist(Pk[j]) <= D.first.sqdist(D.second))
        D = {Pk[i],Pk[j]};
    }
    for(int j = i+1; j < Pk.size(); ++j) {
      if(sq(Pk[i].y-Pk[j].y) > d) break;
      if(Pk[i].sqdist(Pk[j]) <= D.first.sqdist(D.second))
        D = {Pk[i],Pk[j]};
    }
  }
 
  return D;
}

template <typename T>
pair<Point2D<T>, Point2D<T>> nearestPoints(vector<Point2D<T>> &P) {
  sort(P.begin(), P.end(), [](const Point2D<T> &p1, const Point2D<T> &p2) {
    if (p1.x == p2.x) return p1.y < p2.y;
    return p1.x < p2.x;
  });

  return nearestPoints(P, 0, P.size()-1);
}