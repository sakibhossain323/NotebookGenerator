namespace ct {
int par[N], cnt[N], cntp[N];
LL sum[N], sump[N];
void activate(int u) {
  int v = u, _u = u;

  ans += sum[u];
  cnt[u]++;
  while (par[u] != -1) {
    u = par[u];
    LL d = ta ::dis(_u, u);
    ans += sum[u] - sump[v];
    ans += d * (cnt[u] - cntp[v]);

    sum[u] += d;
    cnt[u]++;

    sump[v] += d;
    cntp[v]++;

    v = u;
  }
}
}
namespace ctrd {
int sz[N];
bool blk[N];

int szCalc(Tree &T, int u, int p = -1) {
  sz[u] = 1;
  for (int v : T[u]) {
    if (v == p or blk[v]) continue;
    sz[u] += szCalc(T, v, u);
  }
  return sz[u];
}
int getCentroid(Tree &T, int u, int s, int p = -1) {
  for (int v : T[u]) {
    if (v == p or blk[v]) continue;
    if (sz[v] * 2 >= s) return getCentroid(T, v, s, u);
  }
  return u;
}

void decompose(Tree &T, int u, int p = -1) {
  szCalc(T, u);
  u = getCentroid(T, u, sz[u]);
  ct ::par[u] = p;

  blk[u] = 1;
  for (int v : T[u]) {
    if (!blk[v]) decompose(T, v, u);
  }
}
}
