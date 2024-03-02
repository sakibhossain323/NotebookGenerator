#define sz 100007
ll INF = 1e18;
vector<tuple<ll, ll, ll>> edg;
vector<ll> dis(sz, INF);

void bellman_ford(ll n) {
    ll i, brk;
    dis[1] = 0ll;
    for (i = 1; i <= n; i++) {
        brk = 0;
        for (auto [u, v, w] : edg) {
            if (dis[v] > dis[u] + w)
                dis[v] = dis[u] + w; // for directional graph
            else
                brk++;
        }
        if (brk == n)
            break; // optimization
    }
}

bellman_ford(n);
