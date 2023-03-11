const int MOD = 1e9 + 7;
 
template <typename T>
class Matrix : public vector<vector<T>> {
  public:
    Matrix(size_t rows, size_t cols) {
      this->resize(rows);
      for (auto &r : (*this))
        r.resize(cols);
    }
 
    Matrix<T> operator*(Matrix<T> &m) {
      Matrix<T> res(this->size(), m.back().size());
      for (int i = 0; i < this->size(); i++)
        for (int j = 0; j < m.back().size(); j++)
          for (int k = 0; k < m.size(); k++)
            res[i][j] = (res[i][j] + (*this)[i][k]*m[k][j]) % MOD;
      return res;
    }
};
