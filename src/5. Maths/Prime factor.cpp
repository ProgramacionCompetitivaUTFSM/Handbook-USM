// Corre en O(√n)
vector<int> primeFactors(int n) {
    vector<int> factors;
    for (int i = 2; i <= (n*n); i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    if (n > 1) factors.push_back(n);
    return factors;
}