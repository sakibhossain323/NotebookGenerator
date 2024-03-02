vector<int> parent, setSize;
void make_set(int v) {
    parent[v] = v;
    setSize[v] = 1;
}
int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}
void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
if (a != b) {
        if (setSize[a] < setSize[b]) swap(a, b);
        parent[b] = a;
        setSize[a] += setSize[b];
    }
}
int main() {
    int n;
    cin >> n;
    parent.resize(n);
    setSize.resize(n);
    for (int i = 0; i < n; i++)  make_set(i);
}