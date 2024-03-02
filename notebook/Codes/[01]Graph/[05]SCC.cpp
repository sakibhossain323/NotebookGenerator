#include <bits/stdc++.h>
using namespace std;

#define ll long long

const ll sz = 1e5 + 7;
vector<ll> adj[sz];
vector<ll> Radj[sz];
vector<bool> vis(sz);
vector<ll> ord;

void dfs1(ll cur) {
    vis[cur] = 1;
    for (auto nxt : adj[cur]) {
        if (!vis[nxt])
            dfs1(nxt);
    }
    ord.push_back(cur);
}

void dfs2(ll cur) {
    vis[cur] = 1;
    for (auto nxt : Radj[cur]) {
        if (!vis[nxt])
            dfs2(nxt);
    }
}

signed main() {
    // strongly connected component kosaraju's algorithm
    ll n, m, a, b, i;
    cin >> n >> m;
    for (i = 0; i < m; i++) {
        cin >> a >> b;
        adj[a].push_back(b);
        Radj[b].push_back(a);
    }
    for (i = 1; i <= n; i++) {
        if (!vis[i])
            dfs1(i);
    }
    reverse(ord.begin(), ord.end());
    for (i = 1; i <= n; i++)
        vis[i] = 0;
    vector<ll> scc;
    for (auto e : ord) {
        if (!vis[e]) {
            scc.push_back(e);
            dfs2(e);
        }
    }
    if (scc.size() == 1) {
        cout << "YES\n";
        return 0;
    }
    cout << "NO\n";

    for (i = 1; i <= n; i++)
        vis[i] = 0;
    dfs2(scc[0]);
    if (vis[scc[1]])
        cout << scc[0] << " " << scc[1] << "\n";
    else
        cout << scc[1] << " " << scc[0] << "\n";
    return 0;
}
