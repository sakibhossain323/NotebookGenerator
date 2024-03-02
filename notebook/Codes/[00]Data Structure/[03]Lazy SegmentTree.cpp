ll tree[4*MAX], lazy[4*MAX]; // 1-indexed

void build(vector<ll>&a, int b = 0, int e = -1, int v=1)
{
    if(e == -1) e = a.size()-1;

    if(b == e)
    {
        tree[v] = a[b];
        return;
    }
    
    int mid = (b+e)/2;
    build(a, b, mid, 2*v);
    build(a, mid+1, e,2*v+1);
    tree[v] = tree[2*v] + tree[2*v+1];
}

ll query(int l, int r, int b, int e, int v=1, ll carry = 0)
{
    if(b > r || e < l) return 0;
    if(b >= l && e <= r) return tree[v]+carry*(e-b+1);

    int mid = (b+e)/2;
    ll lseg = query(l, r, b, mid, 2*v, carry+lazy[v]);
    ll rseg = query(l, r, mid+1, e, 2*v+1, carry+lazy[v]);
    return lseg + rseg;
}

void update(int l, int r, ll val, int b, int e, int v = 1)
{
    if(b > r || e < l) return;
    if(b >= l && e <= r)
    {
        tree[v]+= (e-b+1)*val;
        lazy[v]+= val;
        return;
    }

    int mid = (b+e)/2;
    update(l, r, val, b, mid, 2*v);
    update(l, r, val, mid+1, e, 2*v+1);
    tree[v] = tree[2*v] + tree[2*v+1]+ (e-b+1)*lazy[v];
}