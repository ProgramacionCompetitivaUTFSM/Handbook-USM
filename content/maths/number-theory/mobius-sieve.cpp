/*
  *Description:* Compute the first values for the mobius funcion in $ O(n log(n)) $.
  *Status:* Tested in codeforces.
*/
vector<int> mobius_sieve(int mxn){
  vector<int> mob(mxn+1);
  mob[1] = 1;
  for (int i = 2; i <= mxn; i++){
    mob[i]--;
    for (int j = 2*i; j <= mxn; j += i)
      mob[j] -= mob[i];
  }
  return mob;
}