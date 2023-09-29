vector<vector<ll>> egg_drop(ll h,ll k){
  vector<vector<ll>> dp(h + 1,vector<ll>(k + 1));
  forn(i,0,k + 1) dp[0][i] = 0;
  forn(i,1,h + 1) dp[i][0] = INT_MAX;
  forn(j,1,k + 1){
    forn(i,1,h + 1){
      ll ans=INT_MAX,x=1,y=i;
      while(x <= y){
        ll mid = (x + y)/2;
        ll bottom = dp[mid - 1][j - 1];
        ll top = dp[i - mid][j];
        ll temp = max(bottom,top);
        if(bottom < top)
          x = mid + 1;
        else y = mid - 1;
        ans = min(ans,temp);
      }
      dp[i][j] = 1 + ans;
      
    }
  }
  return dp;
}
