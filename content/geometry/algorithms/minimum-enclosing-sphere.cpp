/*
 *Description:* Smallest Enclosing Sphere using simulated annealing
 *Time:* O(iterations * n), roughly O(n) with high constant
 *Status:* Tested
 */

template <typename T>
sphere<T> minimum_ennclosing_sphere(vector<point3d<T>> p, int it = 100000) {
  int n = p.size();
  if (n == 0) return sphere<T>();
  if (n == 1) return sphere<T>(p[0], 0);

  point3d<T> c(0, 0, 0);
  for (int i = 0; i < n; i++)
    c = c + p[i];
  c = c / (ld)n;

  ld ratio = 0.1;
  while (it--) {
    int pos = 0;
    for (int i = 1; i < n; i++) {
      if (c.sq_dist(p[i]) > c.sq_dist(p[pos]))
        pos = i;
    }
    c = c + (p[pos] - c) * ratio;
    ratio *= 0.998;
  }
  return sphere(c, c.dist(p[pos]));
}