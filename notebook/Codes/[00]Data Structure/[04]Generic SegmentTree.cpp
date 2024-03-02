template<typename ST, typename LZ> 
class SegmentTree {
private:
    int n;
    ST *tree, identity;
    ST (*merge) (ST, ST);
 
    LZ *lazy, unmark;
    void (*mergeLazy)(int, int, LZ&, LZ);
    void (*applyLazy)(int, int, ST&, LZ);
 
    void  build(vector<ST> &arr, int lo, int hi, int cur=1)
    {
        if(lo == hi)
        {
            tree[cur] = arr[lo-1];
            return; 
        }
        int mid = (hi+lo)/2, left = 2*cur, right = 2*cur+1;
        build(arr, lo, mid, left);
        build(arr, mid+1, hi, right);
        tree[cur] = merge(tree[left], tree[right]);
    }
 
    void propagate(int lo, int hi, int cur)
    {
        applyLazy(lo, hi, tree[cur], lazy[cur]);
        if(lo < hi)
        {
            int mid = (lo+hi)/2, left = 2*cur, right = 2*cur+1;
            mergeLazy(lo, mid, lazy[left], lazy[cur]);
            mergeLazy(mid+1, hi, lazy[right], lazy[cur]);
        }
        lazy[cur] = unmark;
    }
 
    void update(int from, int upto, LZ delta, int lo, int hi, int cur=1)
    {
        if(lo>hi) return;
        
        propagate(lo, hi, cur);
        if(from > hi or upto < lo) return;
        if(from<= lo and upto >= hi)
        {
            mergeLazy(lo, hi, lazy[cur], delta);
            propagate(lo, hi, cur);
            return;
        }
        int mid = (lo+hi)/2, left = 2*cur, right = 2*cur+1;
        update(from, upto, delta, lo, mid, left);
        update(from, upto, delta, mid+1, hi, right);
        tree[cur] = merge(tree[left], tree[right]);
    }
 
    ST query(int from, int upto, int lo, int hi, int cur=1)
    {
        if(lo>hi) return identity;
 
        propagate(lo, hi, cur);
        if(from > hi or upto < lo) return identity;
        if(from<= lo and upto >= hi) return tree[cur];
        int mid = (lo+hi)/2, left = 2*cur, right = 2*cur+1;
        ST lseg = query(from, upto, lo, mid, left);
        ST rseg = query(from, upto, mid+1, hi, right);
        return merge(lseg, rseg);
    }
 
public:
    SegmentTree(
        vector<ST> arr, ST (*merge) (ST, ST), ST identity,
        void (*mergeLazy)(int, int, LZ&, LZ),
        void (*applyLazy)(int, int, ST&, LZ), LZ unmark
    ):
        n(arr.size()), merge(merge), identity(identity),
        mergeLazy(mergeLazy), applyLazy(applyLazy), unmark(unmark)
    {
        tree = new ST[n*4];
        lazy = new LZ[n*4];
        build(arr, 1, n);
        fill(lazy, lazy+n*4, unmark);
    }
 
    void update(int from, int upto, LZ delta)
    {
        update(from, upto, delta, 1, n);
    }
 
    ST query(int from, int upto)
    {
        return query(from, upto, 1, n);
    }
 
    ~SegmentTree()
    {
        delete[] tree;
        delete[] lazy;
    }
};
 
 
ll add(ll l, ll r) { return l+r;}
void mergeAdd(int lo, int hi, ll &cur, ll pending) { cur+= pending;}
void applyAdd(int lo, int hi, ll &cur, ll pending) { cur+= pending*(hi-lo+1);}

void solve(int tcase)
{
    vector<ll> a(n);   
    SegmentTree<ll, ll> st(a, add, 0, mergeAdd, applyAdd, 0);
}