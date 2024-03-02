template <typename T> struct sparse_table {
	vector <vector<T>> tbl;
	function < T(T, T) > f;
	T id;

	sparse_table(const vector <T> &v, function <T(T, T)> _f, T _id) : f(_f), id(_id) {
        int n = (int) v.size(), b = __lg(n);
        tbl.assign(b + 1, v);
        for(int k = 1; k <= b; k++) {
            for(int i = 0; i + (1 << k) <= n; i++) {
                tbl[k][i] = f(tbl[k - 1][i], tbl[k - 1][i + (1 << (k - 1))]);
            }
        }
	}
	T query(int l, int r) {
        if(l > r) return id;
        int pow = __lg(r - l + 1);
        return f(tbl[pow][l], tbl[pow][r - (1 << pow) + 1]);
	}
};
