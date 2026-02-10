/*
 *Description:* Given $N$ and real $x gt.eq 0$, finds closest rational $p\/q$ with $p, q lt.eq N$. Obeys $|p\/q - x| lt.eq 1\/(q N)$. $O(log N)$.
 *Status:* KACTL based, not self tested
*/
pair<ll,ll> approximate(ld x, ll N) {
  ll LP = 0, LQ = 1, P = 1, Q = 0;
  ll inf = LLONG_MAX;
  ld y = x;
  for (;;) {
    ll lim = min(P ? (N-LP)/P : inf,
                 Q ? (N-LQ)/Q : inf);
    ll a = (ll)floor(y), b = min(a, lim);
    ll NP = b*P+LP, NQ = b*Q+LQ;
    if (a > b) {
      return (abs(x-(ld)NP/(ld)NQ) <
              abs(x-(ld)P/(ld)Q))
        ? make_pair(NP, NQ) : make_pair(P, Q);
    }
    if (abs(y = 1/(y-(ld)a)) > 3*N)
      return {NP, NQ};
    LP = P; P = NP;
    LQ = Q; Q = NQ;
  }
}
