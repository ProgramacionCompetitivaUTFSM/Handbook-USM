void getDivisors(int n, vector<int> &ans) {
  vector<int> left, right;
  for (int i = 1; i * i <= n; i++)
    if (n % i == 0) {
      if (i != n / i)
        right.push_back(n / i);
      left.push_back(i);
    }
  ans.resize(left.size() + right.size());
  reverse(all(right));
  int i = 0, j = 0;
  while (i < left.size() and j < right.size()) {
    if (left[i] < right[j]) 
      ans[i + j - 1] = left[i++];
    else ans[i + j - 1] = right[j++];
  }
  while(i < left.size()) ans[i + j - 1] = left[i++];    
  while(j < right.size()) ans[i + j - 1] = right[j++];
}
