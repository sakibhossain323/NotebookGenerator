
ll bfs(grid &edg, ll sn){
  ll cn=edg.size(), lv=-1, cl=0, nl=1, at, ls;
  vi vst(cn+1, 0), prt(cn+1, -1);
  queue<ll> call;
  call.push(sn); vst[sn]++;
  while(!call.empty()){
    if(!cl){
      lv++; cl=nl; nl=0;
    }

    at=call.front();
    //if(at==en) return lv;
    call.pop(); cl--; ls=at;
    for(ll to:edg[at]){
      if(!vst[to]){

        prt[to]=at;
        call.push(to);
        vst[to]++;
        nl++;
      }
    }
  }
  return 0;
  //return ls; //for deepest.
}
