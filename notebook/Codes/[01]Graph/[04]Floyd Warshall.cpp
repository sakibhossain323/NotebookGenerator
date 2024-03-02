vector<vector<ll>> w(sz, vector<ll>(sz, inf));

void floyd_warshall(ll n) {
    ll i, j, k;
    for (i = 1; i <= n; i++)
        w[i][i] = 0;
    for (k = 1; k <= n; k++) {
        for (i = 1; i <= n; i++) {
            for (j = 1; j <= n; j++) {
                w[j][i] = w[i][j] = min(w[i][j], w[i][k] + w[k][j]); // for bidirectional graph
            }
        }
    }
}

w[b][a] = w[a][b] = min(c, w[a][b]); // for bidirectional graph
floyd_warshall(n);
