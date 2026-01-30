/*
 *Description:* 3D Sphere defined by center point and radius.
 Supports containment testing with epsilon tolerance.
 *Status:* Tested
*/
template <typename T> struct sphere {
  point3d<T> center;
  ld radius;
  sphere() : center(), radius(0) {}
  sphere(point3d<T> c, ld r) : center(c), radius(r) {}
  bool contains(const point3d<T> &pt) const {
    return center.sq_dist(pt) <= radius * radius + 1e-9;
  }
};