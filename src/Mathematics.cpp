#define gcd(a, b) __gcd(a, b)
#define lcm(a, b) gcd(a, b) ? (a / gcd(a, b) * b) : 0
const double PI = 3.1415926535897932384626433832795;
const ll PRIME_BASE = (1 << 61) - 1;