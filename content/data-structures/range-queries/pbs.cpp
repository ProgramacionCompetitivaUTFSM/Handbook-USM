/*
 *Description:* Allow us to perform Q binary searches in log(Q) rounds
 *Status:* Tested on CSES
*/
struct query {
  ll l, r, i;
};
template<class T, class T2>
struct pbs {
  vector<T> ans;
  T2 ds;
  void solve(ll l, ll r, vector<query>& Q) {
    if (Q.empty()) return;
    if (r-l<=1) {
      for (auto q: Q) ans[q.i] = r;
      return;
    }
    ll mid = (l+r)/2, chk = ds.get_state();
    for (ll i = l; i <= mid; i++) ds.apply(i);
    vector<query> L, R;
    for (auto q: Q)
      (ds.check(q)? L : R).push_back(q);
    solve(mid, r, R);
    ds.rollback(chk);
    solve(l, mid, L);
  }
  template<typename... Args>
  pbs(ll l, ll r, vector<query> &Q, Args... args) {
    ds = T2(args...);
    ans.resize(Q.size());
    solve(l, r, Q);
  }
};
