/*
 *Description:* Just a 2D Point
 *Status:* Tested
 */
template <typename T> struct point2d {
  T x, y;
  point2d(){};
  point2d(T x_, T y_) : x(x_), y(y_) {}
  point2d<T> &operator+=(point2d<T> t) {
    x += t.x, y += t.y;
    return *this;
  }
  point2d<T> operator-(point2d<T> t) { return {x - t.x, y - t.y}; }
  point2d<T> operator+(point2d<T> t) { return {x + t.x, y + t.y}; }
  point2d<T> operator*(T t) { return {x * t, y * t}; }
  point2d<T> operator/(T t) { return {x / t, y / t}; }
  point2d<T> &operator-=(point2d<T> t) {
    x -= t.x, y -= t.y;
    return *this;
  }
  T operator|(point2d<T> b) { return x * b.x + y * b.y; }
  T operator^(point2d<T> b) { return x * b.y - y * b.x; }
  T cross(point2d<T> a, point2d<T> b) { return (a - *this) ^ (b - *this); }
  T norm() { return (*this) | (*this); }
  T sqdist(point2d<T> b) { return ((*this) - b).norm(); }
  double abs() { return sqrt(norm()); }
};
template <typename T> point2d<T> operator*(T a, point2d<T> b) { return b * a; }
