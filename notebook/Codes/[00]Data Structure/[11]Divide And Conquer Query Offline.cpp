namespace up {
int l[N], r[N], u[N], v[N], tm;
void push(int _l, int _r, int _u, int _v) {
  l[tm] = _l, r[tm] = _r, u[tm] = _u, v[tm] = _v;
  tm++;
}
}  // namespace up
namespace que {
int node[N], tm;
LL ans[N];
void push(int _node) { node[++tm] = _node; }
}  // namespace que
namespace edge_set {
void push(int i) { dsu ::merge(up ::u[i], up ::v[i]); }
void pop(int t) { dsu ::rollback(t); }
int time() { return dsu ::op.size(); }
LL query(int u) { return a[dsu ::root(u)]; }
}  // namespace edge_set
namespace dncq {
vector<int> tree[4 * N];
void update(int idx, int l = 0, int r = que ::tm, int node = 1) {
  int ul = up ::l[idx], ur = up ::r[idx];
  if (r < ul or ur < l) return;
  if (ul <= l and r <= ur) {
    tree[node].push_back(idx);
    return;
  }
  int m = l + r >> 1;
  update(idx, l, m, node << 1);
  update(idx, m + 1, r, node << 1 | 1);
}
void dfs(int l = 0, int r = que ::tm, int node = 1) {
  int cur = edge_set ::time();
  for (int e : tree[node]) edge_set ::push(e);
  if (l == r) {
    que ::ans[l] = edge_set ::query(que ::node[l]);
  } else {
    int m = l + r >> 1;
    dfs(l, m, node << 1);
    dfs(m + 1, r, node << 1 | 1);
  }
  edge_set ::pop(cur);
}
}  // namespace dncq
void push_updates() {
  for (int i = 0; i < up ::tm; i++) dncq ::update(i);
}
