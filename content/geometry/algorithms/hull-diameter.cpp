/*
 *Description:* Returns the two points with max distance on a convex hull (CCW, no collinear points). $O(n)$. Uses point2d.
 *Status:* KACTL based, not self tested
*/
template<class T>
array<point2d<T>,2> hull_diameter(vector<point2d<T>>& S) {
  int n = S.size(), j = n < 2 ? 0 : 1;
  pair<T, array<point2d<T>,2>> res = {0, {S[0], S[0]}};
  for (int i = 0; i < j;)
    for (;; j = (j+1)%n) {
      res = max(res, {S[i].sqdist(S[j]), {S[i], S[j]}});
      if (((S[(j+1)%n]-S[j])^(S[i+1]-S[i])) >= 0)
        { i++; break; }
    }
  return res.second;
}
