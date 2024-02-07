/*
*/
// (Solo funciona con coordenadas enteras
// Esto usa el teorema de Pick's
pair<int, int> latticePoints(vector<Point2D<int>> &P) {
  P.push_back(P.front());
  int area = 0, bounds = 0;
  for(int i = 0; i < P.size()-1; ++i) {
    area += P[i]^(P[i+1]);
    Point2D<int> p = P[i+1]-P[i];
    bounds += abs(__gcd(p.x, p.y));
  }
  int inside = (abs(area) - bounds + 2)/2;
  // Dejar el poligono como estaba antes
  P.pop_back();
  return {inside, bounds};
}