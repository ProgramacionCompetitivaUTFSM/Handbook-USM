/*
 *Description:* Given $N$ non-negative weights $w$ and target $t$, computes max $S lt.eq t$ that is a subset sum. $O(N max(w_i))$.
 *Status:* KACTL based, not self tested
*/
int knapsack(vector<int> w, int t) {
  int a = 0, b = 0, n = w.size(), x;
  while (b < n && a + w[b] <= t) a += w[b++];
  if (b == n) return a;
  int m = *max_element(w.begin(), w.end());
  vector<int> u, v(2*m, -1);
  v[a+m-t] = b;
  for (int i = b; i < n; i++) {
    u = v;
    for (x = 0; x < m; x++)
      v[x+w[i]] = max(v[x+w[i]], u[x]);
    for (x = 2*m; --x > m;)
      for (int j = max(0, u[x]); j < v[x]; j++)
        v[x-w[j]] = max(v[x-w[j]], j);
  }
  for (a = t; v[a+m-t] < 0; a--) ;
  return a;
}
