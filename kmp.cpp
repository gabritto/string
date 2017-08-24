#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> brd(string pat) {
    int m = pat.size();
    vector<int> border(m + 1, 0);
    int i = 1, j = 0;
    while(i + j < m) {
        while(i + j < m && pat[i + j] == pat[j]) {
            j += 1;
            border[i + j] = j;
        }
        i += min(1, j - border[j]);
        j = border[j];
    }
    return border;
}

vector<int> kmp(string txt, string pat, vector<int> border) {
    int n = txt.size(), m = pat.size();
    vector<int> occ;
    int i = 0, j = 0;
    while(i <= n - m) {
        while(j < m && txt[i + j] == pat[j]) {
            j += 1;
        }
        if(j == m) {
            occ.push_back(i);
        }
        i += min(1, j - border[j]);
        j = border[j];
    }
    return occ;
}

template <class T>
ostream& operator <<(ostream &out, vector<T> v) {
    for(T e: v) {
        out << e << " ";
    }
    return out;
}


int main() {
    string txt, pat;
    cin >> txt >> pat;
    cout << kmp(txt, pat, brd(pat)) << endl; 
    return 0;
}
