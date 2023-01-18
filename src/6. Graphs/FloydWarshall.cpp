void FloydWarshall() {
  for(int k = 0; k < n; k++) {
    for(int i = 0; i < n; i++) {
      for(int j = 0; j < n; j++) {
        D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
      }
    }
  }
}
