vector<pair<ll, ll>> LIS(vector<ll> &v){
  ll n=v.size();
  vector<pair<ll, ll>> seq(n); //{size, last element}
  set<ll> s; //multiset for non_dcrs
  for(int i=0; i<n; ++i){
    auto it=s.lower_bound(v[i]);
    if(it==s.end()) s.insert(v[i]);
    else{
      s.erase(it);
      s.insert(v[i]);
    } 
    seq[i]={s.size(), *(s.rbegin())};
  }
  return seq;
} //seq[i] = {size of LIS in v[0, i], largest element in that sequence}