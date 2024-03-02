for(int mask= 0; mask < (1 << 4); mask++){
    ll sum_of_set = 0;
    for(int i = 0; (1ll << i) <= mask; i++) if(mask& (1ll << i)) sum_of_set += v[i];
    if(sum_of_set == S){
        cout << "Yes\n";
        flg = true;
        break;
    }
}
if(!flg) cout << "No\n";