/*
 *Description:* Minimum enclosing circle, Welzl algorithm $O(n)$ expected
 *Status:* Tested
 */
circle<ld> minimum_enclosing_circle(vector<point2d<ld>> p) {
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  shuffle(p.begin(), p.end(), rng); 
  int n = p.size();
  if (n == 0) return circle<ld>();
  circle<ld> cur(p[0], 0);
  auto out = [&](int i) { return sign(sqrtl(cur.c.sqdist(p[i])) - cur.r) > 0; };
  for (int i = 1; i < n; i++) if (out(i)) {
    cur = circle<ld>(p[i], 0);
    for (int j = 0; j < i; j++  ) if (out(j)) {
      cur = circle<ld>((p[i] + p[j]) / 2, sqrtl(p[i].sqdist(p[j])) / 2);
      for (int k = 0; k < j; k++) if (out(k))
        cur = circle<ld>(p[i], p[j], p[k]);
    }
  }
  return cur;
}