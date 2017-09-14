#include <bits/stdc++.h>

using namespace std;

int levdist(const string &s, const string &t, vector<vector<int>> &memo, int i, int j) {
    if(i < 0) return j + 1;
    if(j < 0) return i + 1;
    if(memo[i][j] != -1)
        return memo[i][j];
    memo[i][j] = (i + 1) * (j + 1);
    int d = 1;
    if(s[i] == t[j])
        d = 0;
    memo[i][j] = min(memo[i][j], d + levdist(s, t, memo, i - 1, j - 1));
    memo[i][j] = min(memo[i][j], 1 + levdist(s, t, memo, i - 1, j));
    memo[i][j] = min(memo[i][j], 1 + levdist(s, t, memo, i, j - 1));
    return memo[i][j];
}

int sellers(const string &p, const string &t, vector<vector<int>> &memo, int i, int j) {
    if(i < 0) return 0;
    if(j < 0) return i + 1;
    if(memo[i][j] != -1)
        return memo[i][j];
    memo[i][j] = (i + 1) * (j + 1);
    int d = 1;
    if(p[i] == t[j])
        d = 0;
    memo[i][j] = min(memo[i][j], d + sellers(p, t, memo, i - 1, j - 1));
    memo[i][j] = min(memo[i][j], 1 + sellers(p, t, memo, i - 1, j));
    memo[i][j] = min(memo[i][j], 1 + sellers(p, t, memo, i, j - 1));
    return memo[i][j];
}



int main() {
    string s, t;
    int r;
    cin >> s >> t >> r;
    int m = s.size(), n = t.size();
    vector<vector<int>> memo(m, vector<int>(n, -1));
    for(int i = -1; i < n; ++i) {
        //cout << sellers(s, t, memo, m - 1, i) << endl;
        
        if(sellers(s, t, memo, m - 1, i) <= r) {
            cout << i << " ";
        }
        /**/
    }
    cout << endl;
    return 0;
}
