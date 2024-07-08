/*
 *Description:* Sort the point depending their angle
 *Status:* Not tested
*/
template <typename T>
int semiplane(Point2D<T> p) { return p.y > 0 or (p.y == 0 and p.x > 0); }

template <typename T>
void orderByAngle(vector<Point2D<T>> &P) {
  sort(P.begin(), P.end(), [](Point2D<T> &p1, Point2D<T> &p2) {
    int s1 = semiplane(p1), s2 = semiplane(p2);
    return s1 != s2 ? s1 > s2 : (p1^p2) > 0;
  });
}