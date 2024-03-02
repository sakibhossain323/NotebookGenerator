const ll sz = 1e5 + 7;
vector<ll> pr(sz);

ll find(ll x) {
    if (pr[x] == x) return x;
    return pr[x] = find(pr[x]);
}

void _union(ll x, ll y) {
    pr[find(y)] = find(x);
}

signed main() {
    ll n, m, i;
    cin >> n >> m;
    vector<tuple<ll, ll, ll>> edg(m);
    iota(pr.begin(), pr.begin() + n + 1, 0);
    for (auto &[w, u, v] : edg) cin >> u >> v >> w;
    sort(edg.begin(), edg.end());

    ll cost = 0;
    for (auto [w, u, v] : edg) {
        if (find(u) != find(v)) {
            _union(u, v);
            cost += w;
        }
    }
    for (i = 1; i < n; i++) {
        if (find(i) != find(i + 1)) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    cout << cost << "\n";
}
