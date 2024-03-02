const ll m = 10e6;
vector<ll> lp(m+1);
vector<ll> prime;
void ln_sieve() {
    for(ll i = 2; i <= m; i++){
        if(!lp[i]){
            lp[i] = i;
            prime.push_back(i);
        }

        for(ll j = 0; i * prime[j] <= m; j++){
            lp[i * prime[j]] = prime[j];
            if(prime[j] == lp[i]) break;
        }
    }
}