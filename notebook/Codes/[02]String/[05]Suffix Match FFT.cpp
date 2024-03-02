// Find occurrences of t in s where '?'s are automatically matched with any character
// res[i + m - 1] = sum_j=0 to m - 1 { s[i + j] * t[j] * (s[i + j] - t[j]) }
vector<int> string_matching(string &s, string &t) {
    int n = s.size(), m = t.size();
    vector<int> s1(n), s2(n), s3(n);
    for(int i = 0; i < n; i++)
        s1[i] = s[i] == '?' ? 0 : s[i] - 'a' + 1; // assign any non zero number for non '?'s
    for(int i = 0; i < n; i++)
        s2[i] = s1[i] * s1[i];
    for(int i = 0; i < n; i++)
        s3[i] = s1[i] * s2[i];
    
    vector<int> t1(m), t2(m), t3(m);
    for(int i = 0; i < m; i++)
        t1[i] = t[i] == '?' ? 0 : t[i] - 'a' + 1;
    for(int i = 0; i < m; i++)
        t2[i] = t1[i] * t1[i];
    for(int i = 0; i < m; i++)
        t3[i] = t1[i] * t2[i];
    
    reverse(t1.begin(), t1.end());
    reverse(t2.begin(), t2.end());
    reverse(t3.begin(), t3.end());
    
    vector<int> s1t3 = multiply(s1, t3);
    vector<int> s2t2 = multiply(s2, t2);
    vector<int> s3t1 = multiply(s3, t1);
    
    vector<int> res(n);
    for(int i = 0; i < n; i++)
        res[i] = s1t3[i] - s2t2[i] * 2 + s3t1[i];
    
    vector<int> oc;
    for(int i = m - 1; i < n; i++)
        if(res[i] == 0)
            oc.push_back(i - m + 1);
    
    return oc;
}
