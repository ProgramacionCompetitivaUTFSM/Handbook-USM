/*
 *Description:* Sort the points depending the angle
 *Status:* Not tested
*/
template <typename T>
void order_by_slope(vector<point2d<T>> &P) {
  sort(P.begin(), P.end(), [](const point2d<T> &p1, const point2d<T> &p2) {
    Fraction<T> r1 = Fraction<T>(p1.x, p1.y), r2 = Fraction<T>(p2.x, p2.y);
    return r2 < r1;
  });
}