// Number of paths of fixed length

// G = (V, E) undirected, |V| = n, int k
// For each (i, j) find the number of paths between (i, j) that has length = k
//
// Algorithm: C_k is the matrix for case k
// G = C1 = adj matrix: G[i][j] = 1 if there is an edge otherwise 0
// Then C_{k+1} = C_k * G or C_k = G^k
// Complexity: O(n^3*logk)



// Shortest path of fixed length

// G = (V, E) undirected, |V| = n, int k
// For each (i, j) find the minimum length path between (i, j) that has k edges
//
// Algorithm: L_k is that matrix for case k
// G = L_1 = adj matrix: G[i][j] = wij if there is an edge otherwise INF
// Then L_{k+1}[i][j] = min(L_k[i][p]+G[p][j]) with p in [1, n]
// Or L_{k+1} = L_k + G with + operation: Taking mininum instead of sum
// Then L_k = G^(+k)
// Complexity: O(n^3*logk)



// Generization for <= k
// Number of paths:
//      Duplicate each v -> v': Add edge (v, v'), loop (v', v')
//      Then #(path(i, j) with length <= k) == #(path(i, j') with length = k+1)
// Shortest path:
//      Duplicate each v -> v': Adad edge (v, v') and loop (v', v') with weight = 0
//      Then min(path(i, j) with length <= k) == min(path(i, j') with length = k+1)
