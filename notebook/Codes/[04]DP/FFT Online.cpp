void fftOnline(vector <LL> &a, vector <LL> b) {
    int n = a.size();
    auto call = [&](int l, int r, auto &call){
        if(l >= r) return;
        int mid = l + r >> 1;
        call(l, mid, call);

        vector <LL> _a(a.begin() + l, a.begin() + mid + 1);
        vector <LL> _b(b.begin(), b.begin() + (r - l + 1));
        auto c = fft :: anyMod(_a, _b);

        for(int i = mid + 1; i <= r; i++) {
            a[i] += c[i - l];
            a[i] -= (a[i] >= mod) * mod;
        }
        call(mid + 1, r, call);
    };
    call(0, n - 1, call);
}

