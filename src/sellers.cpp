#include <vector>
#include <string>
#include <algorithm>

using namespace std;

namespace sellers {

static vector<string> patterns;
static int err;

void build(const vector<string> &pats, int r) {
    patterns = pats;
    err = r;
}

int search(const string &txt) {
    int occ = 0;
    int n = txt.size();
    for(const string &pat: patterns) {
        int m = pat.size();
        vector<vector<int>> memo(2, vector<int>(n + 1));
        int old = 0, cur = 1;
        for(int i = 0; i <= n; ++i) {
            memo[old][i] = 0;
        }
        for(int i = 1; i <= m; ++i) {
            memo[cur][0] = 0;
            for(int j = 1; j <= m; ++j) {
                memo[cur][j] = min(memo[cur][j - 1] + 1, memo[old][j] + 1);
                int b = 0;
                if(pat[i - 1] != txt[j - 1])
                    b = 1;
                memo[cur][j] = min(memo[cur][j], b + memo[old][j - 1]);
            }
            swap(old, cur);
        }
        for(int j = 1; j <= n; ++j) {
            if(memo[old][j] <= err) {
                occ += 1;
            }
        }
    }
    return occ;
}

} //namespace sellers
