using Tree = vector<vector<int>>;
int anc[B][N], sz[N], lvl[N], st[N], en[N], nxt[N], t = 0;

void initLifting(int n) {
  for (int b = 1; b < B; b++) {
    for (int i = 0; i < n; i++) {
      anc[b][i] = anc[b - 1][anc[b - 1][i]];
    }
  }
}

int kthAncestor(int u, int k) {
  for (int b = 0; b < B; b++) {
    if (k >> b & 1) u = anc[b][u];
  }
  return u;
}

int lca(int u, int v) {
  if (lvl[u] > lvl[v]) swap(u, v);
  v = kthAncestor(v, lvl[v] - lvl[u]);

  if (u == v) return u;

  for (int b = B - 1; b >= 0; b--) {
    if (anc[b][u] != anc[b][v]) u = anc[b][u], v = anc[b][v];
  }
  return anc[0][u];
}

int dis(int u, int v) {
  int g = lca(u, v);
  return lvl[u] + lvl[v] - 2 * lvl[g];
}
bool isAncestor(int u, int v) { return st[v] <= st[u] and en[u] <= en[v]; }

void tour(int u, int p, Tree &T) {
  st[u] = t++;
  int idx = 0;
  for (int v : T[u]) {
    if (v == p) continue;
    nxt[v] = (idx++ ? v : nxt[u]);  // only for hld
    anc[0][v] = u, lvl[v] = lvl[u] + 1;
    tour(v, u, T);
  }
  en[u] = t;  // [st, en] contains subtree range
}

void hld(int u, int p, Tree &T) {
  sz[u] = 1;

  int eld = 0, mx = 0, idx = 0;
  for (int i = 0; i < T[u].size(); i++) {
    int v = T[u][i];
    if (v == p) continue;
    hld(v, u, T);

    if (sz[v] > mx) mx = sz[v], eld = i;
    sz[u] += sz[v];
  }
  swap(T[u][0], T[u][eld]);
}

LL climbQuery(int u, int g) {
  LL ans = -INF;
  while (1) {
    int _u = nxt[u];
    if (isAncestor(g, _u)) _u = g;
    ans = max(ans, rmq ::query(st[_u], st[u]));

    if (_u == g) break;
    u = anc[0][_u];
  }
  return ans;
}

LL pathQuery(int u, int v) {
  int g = lca(u, v);
  return max(climbQuery(u, g), climbQuery(v, g));
}

void init(int u, Tree &T) {
  int n = T.size();
  anc[0][u] = nxt[u] = u;
  lvl[u] = 0;
  hld(u, u, T);
  tour(u, u, T);
  initLifting(n);
}
