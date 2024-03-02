class HashedString {
private:
    static const long long M = 1e9 + 7;
    static const long long B = 256;
    static vector<long long> pow;
    vector<long long> p_hash;

public:
    HashedString(const string& s) : p_hash(s.size() + 1) {
        while (pow.size() < s.size()) {
            pow.push_back((pow.back() * B) % M);
        }
        p_hash[0] = 0;
        for (int i = 0; i < s.size(); i++) {
            p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
        }
    }

    long long getHash(int start, int end) {
        long long raw_val = (
            p_hash[end + 1] - (p_hash[start] * pow[end - start + 1])
        );
        return (raw_val % M + M) % M;
    }
};

vector<long long> HashedString::pow = {1};
