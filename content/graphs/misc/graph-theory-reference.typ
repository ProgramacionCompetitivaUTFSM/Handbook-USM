*Matrix-Tree theorem:* Create $N times N$ matrix `mat`. For each edge $a -> b in G$: `mat[a][b]--, mat[b][b]++` (and `mat[b][a]--, mat[a][a]++` if undirected). Remove $i$-th row and column, take determinant: yields \#directed spanning trees rooted at $i$ (if undirected, remove any row/column).

*Erdős–Gallai theorem:* A simple graph with degrees $d_1 gt.eq dots.c gt.eq d_n$ exists iff $d_1 + dots.c + d_n$ is even and for every $k = 1, dots, n$:
$ sum_(i=1)^k d_i lt.eq k(k-1) + sum_(i=k+1)^n min(d_i, k) $
