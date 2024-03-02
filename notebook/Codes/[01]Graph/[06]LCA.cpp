LL n, l, timer;
vector<vector<LL>> adj;
vector<LL> tin, tout;
vector<vector<LL>> up;
void dfs(LL v, LL p) {
    tin[v] = ++timer;
    up[v][0] = p;
    for (LL i = 1; i <= l; ++i)
        up[v][i] = up[up[v][i-1]][i-1];
    for (LL u : adj[v]) {
        if (u != p) dfs(u, v);
    }
    tout[v] = ++timer;
}
bool is_ancestor(LL u, LL v)  {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}
LL lca(LL u, LL v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (LL i = l; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) u = up[u][i];
    }
    return up[u][0];
}
void preprocess(LL root) {
    tin.resize(n);
    tout.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<LL>(l + 1));
    dfs(root, root);
}