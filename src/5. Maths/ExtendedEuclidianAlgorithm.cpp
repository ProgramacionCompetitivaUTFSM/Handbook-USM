struct GCD_type { ll x, y, d; };
GCD_type ex_GCD(ll a, ll b){
    if (b == 0) return {1, 0, a};
    GCD_type pom = ex_GCD(b, a % b);
    return {pom.y, pom.x - a / b * pom.y, pom.d};
}
