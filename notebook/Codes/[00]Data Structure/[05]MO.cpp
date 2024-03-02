struct node {
    LL l, r, idx;
};
bool cmp(const node &x, const node &y) {
    return x.r < y.r;
}
void add(LL x) {
    if(mp[x] % 2) curr++;
    mp[x]++;
}
void diminish(LL x) {
    if(mp[x] % 2 == 0) curr--;
    mp[x]--;
}
void solve()
{
    BLOCK_SIZE = sqrt(n) + 1;
    rep(i, 0, q-1) {
        LL x, y; cin >> x >> y;
        x--; y--;
        query[x / BLOCK_SIZE].pb({x, y, i});
        m = max(m, x / BLOCK_SIZE);
    }
    rep(i, 0, m) sort(all(query[i]), cmp);
    LL mo_left = 0, mo_right = -1;
    rep(i, 0, m) {
        for(auto [left, right, id] : query[i]) {
            while(mo_right < right) add(v[++mo_right]);
            while(mo_right > right) diminish(v[mo_right--]);
            while(mo_left < left) diminish(v[mo_left++]);
            while(mo_left > left) add(v[--mo_left]);
            answer[id] = curr;
        }
    }
    rep(i, 0, q-1) cout << answer[i] << endl;
}