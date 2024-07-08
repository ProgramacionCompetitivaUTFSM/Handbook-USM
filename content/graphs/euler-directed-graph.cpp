bool euler_directed_graph(vector<vector<int>> &adj, vector<int> &path){
  path.resize(0);
  int n = adj.size();
  vector<int> indeg(n), outdeg(n);
  int v1 = -1, v2 = -1;
  for (int i = 0; i < n; i ++){
    outdeg[i] = adj[i].size();
    for (int x : adj[i])
      indeg[x] ++;
  }
  for (int i = 0; i < n; i ++){
    int dif = outdeg[i] - indeg[i];
    if (dif == 1){
      if (v1 == -1) v1 = i;
      else return false;
    }
    else if (dif == -1){
      if (v2 == -1) v2 = i;
      else return false;
    }
    else if (dif != 0) return false;
  }
  if (v1 != v2 and (v1 == -1 or v2 == -1)) return false;
  int first = v1;
  if (v1 != -1) adj[v2].push_back(v1);
  else 
    for (int i = 0; i < n; i ++)
      if (outdeg[i] > 0)
        first = i;
  stack<int> st;
  st.push(first);
  vector<int> res;
  while(!st.empty()){
    int v = st.top();
    if (outdeg[v] == 0){
      res.push_back(v);
      st.pop();
    }
    else{
      st.push(adj[v][0]);
      outdeg[v] --;
      swap(adj[v][0], adj[v][outdeg[v]]);
    }
  }
  for (int i = 0; i < n; i ++)
    if (outdeg[i] != 0)
      return false;
  reverse(res.begin(), res.end());
  if (v1 != -1){
    for (int i = 0; i + 1 < res.size(); i ++){
      if (res[i] == v2 && res[i + 1] == v1){
        vector<int> res2(res.begin() + i + 1, res.end());
        res2.insert(res2.end(), res.begin(), res.begin() + i + 1);
        res = res2;
        break;
      }
    }
  }
  path = res;
  return true;
}
