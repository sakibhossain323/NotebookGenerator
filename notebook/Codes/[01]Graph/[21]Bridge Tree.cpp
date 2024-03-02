vector<vector<int>> comps;
vector<int> depth, low, id;
stack<int> st;
vector<Edge> bridges;
Graph tree;

void dfs(int u, Graph &G, int ed = -1, int d = 0) {
  low[u] = depth[u] = d;
  st.push(u);
  for (int e : G[u]) {
    if (e == ed) continue;
    int v = G(e).to(u);
    if (depth[v] == -1) dfs(v, G, e, d + 1);
    low[u] = min(low[u], low[v]);

    if (low[v] <= depth[u]) continue;
    bridges.emplace_back(u, v);
    comps.emplace_back();
    do {
      comps.back().push_back(st.top()), st.pop();
    } while (comps.back().back() != v);
  }
  if (ed == -1) {
    comps.emplace_back();
    while (!st.empty()) comps.back().push_back(st.top()), st.pop();
  }
}
Graph &createTree() {
  for (auto &comp : comps) {
    int idx = tree.addNode();
    for (auto &e : comp) id[e] = idx;
  }
  for (auto &[l, r] : bridges) tree.addEdge(id[l], id[r]);
  return tree;
}

void init(Graph &G) {
  int n = G.n;
  depth.assign(n, -1), id.assign(n, -1), low.resize(n);
  for (int i = 0; i < n; i++) {
    if (depth[i] == -1) dfs(i, G);
  }
}
