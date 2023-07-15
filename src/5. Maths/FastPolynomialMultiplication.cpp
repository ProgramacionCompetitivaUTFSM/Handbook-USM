template<typename T>
vector<T> FPM(vector<T> &a, vector<T> &b) {
  vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1; while (n < a.size()+b.size()) n <<= 1;
  fa.resize(n), fb.resize(n);
  FFT(fa, false); FFT(fb, false);
  for (int i = 0; i < n; i++)
    fa[i] *= fb[i];
  FFT(fa, true);
  vector<T> R(n);
  for (int i = 0; i < n; i++)
    R[i] = round(fa[i].real());
  return R;
}
