/*
 *Description:* Allow us to find cycles in any function
 *Status:* Not tested
*/
template<typename T, T f(T)>
pair<ll, ll> tortoise_hare(T x0) {  
  T t = f(x0); T h = f(f(x0));
  while(t != h) t = f(t), h = f(f(h));
  ll mu = 0; t = x0;
  while(t != h) t = f(t), h = f(h), mu++;
  ll lam = 1; h = f(t);
  while(t != h)h = f(h), lam += 1;
  // mu = start, lam = period
  return {mu, lam};
}