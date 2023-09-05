// Puedes usar __int128_t como un numero entero normal, con 128 bits.
// No esta definido en la libreria estandar la entrada y salida, pero aqui
// estan implementados!! Es algo lento asi que hay que tener cuidado
__int128_t read128_t() {
  string S; cin >> S;
  if (S == "0") return 0;
  __int128_t res = 0;
  for (int i = S[0] == '-' ? 1 : 0; i < (int)S.size(); i++)
    res = res * 10 + S[i] - '0';
  if (S[0] == '-') res = -res;
  return res;
}
string parse128_t(i128 x) {
  if (x == 0) return "0";
  bool neg = false;
  if (x < 0) neg = true, x = -x;
  string res;
  while (x) res.push_back(x % 10 + '0'), x /= 10;
  if (neg) res.push_back('-');
  reverse(begin(res), end(res));
  return res;
}
