/*
 *Description:* How many integers point are inside or in the bounds of the polygon
 - Only works for integers points
 *Status:* Tested on CSES
*/
pair<ll, ll> lattice_points(vector<point2d<ll>> &P) {
  P.push_back(P.front());
  ll area = 0, bounds = 0;
  for(int i = 0; i < (int)P.size()-1; ++i) {
    area += P[i]^(P[i+1]);
    point2d<ll> p = P[i+1]-P[i];
    bounds += abs(__gcd(p.x, p.y));
  }
  ll inside = (abs(area) - bounds + 2)/2;
  // Dejar el poligono como estaba antes
  P.pop_back();
  return {inside, bounds};
}