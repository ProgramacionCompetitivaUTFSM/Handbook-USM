// Shuffle en O(n)
void fisherYates(vector<int> &arr) {
    mt19937 gen(random_device());
    uniform_int_distribution<int> dist(0, arr.size() - 1);
    for (int i = arr.size()-1; i > 0; i--)
        swap(arr[i], arr[dist(gen)]);
}
