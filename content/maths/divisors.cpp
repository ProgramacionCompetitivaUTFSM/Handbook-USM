/*
  *Author:* Sebastian Torrealba
  *Description:* Get all divisors in $O( sqrt(n) )$, it includes $1$ and $n$
  *Status:* Highly tested
*/
vector<ll> get_divisors(ll n) {
  vector<ll> left, right;
  for (ll i = 1; i * i <= n; i++)
    if (n % i == 0) {
      left.push_back(i);
      if (i != n / i)
        right.push_back(n / i);
    }
  reverse(begin(right), end(right));
  for (ll x : right) left.push_back(x);
  return left;
}