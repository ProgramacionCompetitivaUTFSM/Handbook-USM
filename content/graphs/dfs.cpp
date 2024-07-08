/*
 *Description:* Just traverse a graph in dfs order
 *Status*: Tested
*/
void dfs(int s) {
  if (visited[s]) return;
  visited[s] = true;
  // process node s
  for (auto u: adj[s]) {
    dfs(u);
  }
}