template <typename T>
void orderBySlope(vector<Point2D<T>> &P) {
  sort(P.begin(), P.end(), [](const Point2D<T> &p1, const Point2D<T> &p2) {
    Fraction<T> r1 = Fraction<T>(p1.x, p1.y), r2 = Fraction<T>(p2.x, p2.y);
    return r2 < r1;
  });
}
