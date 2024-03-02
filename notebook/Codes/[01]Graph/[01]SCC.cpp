vector<int> order, comp, idx;
vector<bool> vis;
vector<vector<int>> comps;
Graph dag;

void dfs1(int u, Graph &G, string s = "") {
  vis[u] = 1;
  for (int e : G[u]) {
    int v = G(e).to(u);
    if (!vis[v]) dfs1(v, G, s);
  }
  order.push_back(u);
}
void dfs2(int u, Graph &R) {
  comp.push_back(u);
  idx[u] = comps.size();

  for (int e : R[u]) {
    int v = R(e).to(u);
    if (idx[v] == -1) dfs2(v, R);
  }
}

void init(Graph &G) {
  int n = G.n;
  vis.assign(n, 0);
  idx.assign(n, -1);

  for (int i = 0; i < n; i++) {
    if (!vis[i]) dfs1(i, G);
  }
  reverse(order.begin(), order.end());

  Graph R(n);
  for (auto &e : G.edges) R.addEdge(e.v, e.u, 0);

  for (int u : order) {
    if (idx[u] != -1) continue;
    comp.clear();
    dfs2(u, R);
    comps.push_back(comp);
  }
}

Graph &createDAG(Graph &G) {
  int sz = comps.size();
  dag = Graph(sz);

  vector<bool> taken(sz);
  vector<int> cur;

  for (int i = 0; i < sz; i++) {
    cur.clear();
    taken[i] = 1;
    for (int u : comps[i]) {
      for (int e : G[u]) {
        int v = G(e).to(u);
        int j = idx[v];
        if (taken[j]) continue;  // rejects multi-edge
        dag.addEdge(i, j, 0);
        taken[j] = 1;
        cur.push_back(j);
      }
    }
    for (int j : cur) taken[j] = 0;
  }
  return dag;
}
