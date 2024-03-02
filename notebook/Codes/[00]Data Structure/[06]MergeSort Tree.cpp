vector<LL> tree[5*MAXN];
LL A[N];
void build_tree(LL now , LL curLeft, LL curRight) {
     if(curLeft == curRight) {
        tree[now].push_back(A[curLeft]);
        return;
     }
     LL mid = (curLeft + curRight) / 2;
     build_tree(2 * now, curLeft, mid);
     build_tree(2 * now + 1, mid + 1 , curRight);
     tree[now] = merge(tree[2 * now] , tree[2 * now + 1]);
}
LL query(LL now, LL curLeft, LL curRight, LL l, LL r, LL k) {
    if(curRight < l || curLeft > r) return 0;
    if(curLeft >= l && curRight <= r)
        Return lower_bound(tree[now].begin(), tree[now].end(), k) - tree[now].begin();
    LL mid = (curLeft + curRight) / 2;
    return query(2 * now, curLeft, mid, l, r, k) + query(2 * now + 1, mid + 1, curRight, l, r, k);
}