
using ll = long long;
using vi = vector<ll>;
using grid = vector<vi>;

void et(grid &edg, ll at, ll pt, grid &tr, ll &id){
  tr[0][id]=at; //val[at];
  tr[1][at]=id++;

  for(ll to: edg[at]) if(to-pt){
    et(edg, to, at, tr, id);
  }
  tr[0][id]=at; //val[at];
  tr[2][at]=id++;
  return;
}

grid etour(grid &edg, ll rt){
  ll cn=edg.size(), id=1;
  grid tour={vi(2*cn, 0), vi(cn), vi(cn)};
  et(edg, rt, 0, tour, id);
  return tour;
}
