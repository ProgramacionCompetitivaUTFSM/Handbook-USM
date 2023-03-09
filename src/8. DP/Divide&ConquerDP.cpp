#include "../Header.cpp"

// dp(i, j) = min dp(i-1,k-1) + C(k,j) for all k in [0, j]

// C(a,c) + C(b, d) <= C(a,d) + C(b,c) for all a <= b <= c <= d

vp c;
vl acum1, acum2;

ll cost(ll i, ll j)
{
  return c[j].first * (acum1[j+1] - acum1[i]) - (acum2[j+1] - acum2[i]);
}

vector<ll> last, now;

void compute(int l, int r, int optl, int optr)
{
    if (l > r) return;

    int mid = (l + r) / 2;
    pair<ll, int> best = {cost(0, mid), -1};

    for(int k = max(1, optl); k < min(mid, optr) + 1; k++)
        best = min(best, {last[k - 1] + cost(k, mid), k});

    now[mid] = best.first;

    compute(l, mid - 1, optl, best.second);
    compute(mid + 1, r, best.second, optr);
}

int main(){
  ios_base::sync_with_stdio(0);
  cin.tie(0);

    
  ll n, k, x, w;
  while(cin >> n >> k){
    
    c.clear();
    for(int i = 0; i < n; i++){

      cin >> x >> w;
      c.push_back({x, w});
    }

    acum1.clear();
    acum2.clear();
    acum1.push_back(0);
    acum2.push_back(0);

    for(int i = 0; i < n; i++){
      acum1.push_back(c[i].second);
      acum2.push_back(c[i].first * c[i].second);
      acum1.back() += acum1[i];
      acum2.back() += acum2[i];
    }

    last.assign(n, INF);
    now.resize(n);

    for(int i = 0; i < k; i++) { compute(0, n - 1, 0, n - 1); swap(last, now); }

    cout<< last[n-1]<<"\n";

  }
