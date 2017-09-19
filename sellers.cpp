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

void it_sellers(char *pat, char *txt, int r) {
    int m = strlen(pat), n = strlen(txt);
    int **mat = new int*[2];
    for(int i = 0; i < 2; ++i) {
        mat[i] = new int[m + 1];
    }
    
    int old = 0, cur = 1;
    for(int i = 0; i <= n; ++i)
        mat[old][i] = 0;
        
    for(int i = 1; i <= m; ++i) {
        mat[cur][0] = 0;
        for(int j = 1; j <= n; ++j) {
            mat[cur][j] = min(mat[cur][j - 1] + 1, mat[old][j] + 1);
            mat[cur][j] = min(mat[cur][j], (pat[i - 1] != txt[j - 1]) + mat[old][j - 1]);
        }
        swap(cur, old);
    }
    
    for(int j = 1; j <= n; ++j) {
        if(mat[old][j] <= r) {
            /*
                reportar ocorrência terminando em j
            */
        }
    }
    
    for(int i = 0; i < 2; ++i) {
        delete[] mat[i];
    }
    
    delete[] mat;
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
