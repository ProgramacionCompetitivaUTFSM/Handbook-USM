/*
 *Description:* Parallel Binary Search (PBS) allows us to perform Q binary searches in log(Q) rounds.
 - snapshot() Returns the current position in the update history.
 - rollback(chk) Restores the data structure to the chk state.
 *Status:* Tested on CSES
*/
struct query {
  ll l, r, i;
};
template<class T, class T2>
struct PBS {
  vector<T> ans;
  T2 ds;
  void solve(ll l, ll r, vector<query>& Q) {
    if (Q.empty()) return;
    if (r-l<=1) {
      for (auto q: Q) ans[q.i] = r;
      return;
    }
    ll mid = (l+r)/2, chk = ds.snapshot();
    for (ll i = l; i <= mid; i++) ds.apply(i);
    vector<query> L, R;
    for (auto q: Q)
      (ds.check(q)? L : R).push_back(q);
    solve(mid, r, R);
    ds.rollback(chk);
    solve(l, mid, L);
  }
  template<typename... Args>
  PBS(ll l, ll r, vector<query> &Q, Args... args): ds(args...), ans(Q.size()) {
    solve(l, r, Q);
  }
};
