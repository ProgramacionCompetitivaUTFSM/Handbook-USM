/*
  *Description:* Finds a non-trivial factor of a composite number $n$ using Pollard's Rho algorithm.
  *Status:* Partially tested
*/
ll pollard_rho(ll n) {
  if((n&1)^1) return 2;
  ll x = 2, y=2, d=1;
  ll c = rand()%n+1;
  while(d==1) {
    x=(mulmod(x,x,n)+c)%n;
    y=(mulmod(y,y,n)+c)%n;
    y=(mulmod(y,y,n)+c)%n;
    if(x>=y)d=__gcd(x-y,n);
    else d=__gcd(y-x,n);
  }
  return d==n? pollard_rho(n):d;
}
