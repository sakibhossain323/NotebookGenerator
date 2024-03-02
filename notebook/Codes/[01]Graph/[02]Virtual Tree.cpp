namespace lca1 {
int st[N], lvl[N];
int tbl[B][2 * N];
int t = 0;

void dfs(int u, int p, Tree &T) {
  st[u] = t;
  tbl[0][t++] = u;
  for(int v: T[u]) {
    if(v == p) continue;
    lvl[v] = lvl[u] + 1;
    dfs(v, u, T);
    tbl[0][t++] = u;
  }
}
int low(int u, int v) {
  return make_pair(lvl[u], u) < make_pair(lvl[v], v) ? u : v;
}

void makeTable(int n) {
  int m = 2 * n - 1;
  for(int b = 1; b < B; b++) {
    for(int i = 0; i < m; i++) {
      tbl[b][i] = low(tbl[b - 1][i], tbl[b - 1][i + (1 << b - 1)]);
    }
  }
}

int lca(int u, int v) {
  int l = st[u], r = st[v];
  if(l > r) swap(l, r);
  int k = __lg(r - l + 1);
  return low(tbl[k][l], tbl[k][r - (1 << k) + 1]);
}
void init(int root, Tree &T) {
  lvl[root] = 0;
  t = 0;
  dfs(root, root, T);
  makeTable(T.size());
}
}
namespace vt {
int st[N], en[N], t;
vector <int> adj[N];

void dfs(int u, int p, Tree &T) {
  st[u] = t++;
  for(int v: T[u]) if(v != p) dfs(v, u, T);
  en[u] = t++;
}
bool comp(int u, int v) {
  return st[u] < st[v];
}
bool isAncestor(int u, int p) {
  return st[p] <= st[u] and en[u] <= en[p];
}

void construct(vector <int> &nodes) {
  sort(nodes.begin(), nodes.end(), comp);
  int n = nodes.size();
  for(int i = 0; i + 1 < n; i++) {
    nodes.push_back(lca1 :: lca(nodes[i], nodes[i + 1]));
  }
  sort(nodes.begin(), nodes.end(), comp);
  nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());
  n = nodes.size();
  stack <int> s;
  s.push(nodes[0]);
  for(int i = 1; i < n; i++) {
    int u = nodes[i];
    while(not isAncestor(u, s.top())) s.pop();
    adj[s.top()].push_back(u);
    s.push(u);
  }
}
void clear(vector <int> &nodes) {
  for(int u: nodes) {
      adj[u].clear();
  }
}

void init(int root, Tree &T) {
  lca1 :: init(root, T);
  t = 0;
  dfs(root, root, T);
}
}