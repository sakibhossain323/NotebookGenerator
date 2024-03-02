template<int sz>
struct Trie {
    Trie() : id(1) {
        memset(endMark, 0, sizeof endMark);
        for_each(all(trie), [](vector<int> &v) { v.assign(sz, 0); });
    }

    void insert(const string &s) {
        int cur = 0;
        for (auto c : s) {
            int val = c - 'a';
            if (!trie[cur][val])
                trie[cur][val] = id++;
            cur = trie[cur][val];
        }
        endMark[cur] = true;
    }

    bool search(const string &s) {
        int cur = 0;
        for (auto c : s) {
            int val = c - 'a';
            if (!trie[cur][val])
                return false;
            cur = trie[cur][val];
        }
        return endMark[cur];
    }

private:
    int id, endMark[100005];
    vector<int> trie[100005];
};
