/*
 *Description:* Dynamically insert lines of the form y = a*x + b and query for the minimum value at any x in a fixed interval [L, R].
 *Status:* Partially tested
*/
struct Line{
  ll a,b; // ax + b
  Line(ll _a, ll _b) : a(_a), b(_b) {};
  ll eval(ll x){ return a*x + b;}  
};

struct LiChao{  
  const ll INF = 1e18;
  ll L,R; 
  vector<Line> st;
  LiChao(ll l,ll r){
    L = l, R = r+1;
    st = vector<Line>(4*(r - l + 1),Line(0,INF));
  };
  void add(Line nw, ll v, ll l, ll r){
    ll m = (l+r)/2;
    bool lc = nw.eval(l) < st[v].eval(l);
    bool mc = nw.eval(m) < st[v].eval(m);
    if(mc) swap(nw,st[v]);
    if(r - l == 1) return;
    if(lc != mc) add(nw,2*v,l,m);
    else add(nw,2*v + 1,m,r);
  }
  ll get(ll x, ll v, ll l, ll r){
    ll m = (l+r)/2;
    if(r - l == 1) return st[v].eval(x);
    if(x < m) return min(st[v].eval(x),get(x,2*v,l,m));
    return min(st[v].eval(x),get(x,2*v+1,m,r));
  }

  void add(ll a, ll b){add(Line(a,b),1,L,R);};
  ll get(ll x){return get(x,1,L,R);};
};