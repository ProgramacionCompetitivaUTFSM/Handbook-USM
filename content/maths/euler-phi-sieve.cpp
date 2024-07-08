/*
  *Description:* Return $phi(n)$ for all positive $n$, runs on $O(n log(log(n)))$
  *Status:* Not tested
*/
struct euler_phi {
  vector<int> phi;
  euler_phi(int n) {
    phi.resize(n + 1);
    for (int i = 1; i <= n; i++)
      phi[i] = i;          
    for (int i = 2; i <= n; i++) {
      if (phi[i] == i)
        for (int j = i; j <= n; j += i)
          phi[j] = phi[j] / i * (i - 1);
    }
  }
};