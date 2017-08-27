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

template <class T>
ostream& operator <<(ostream &out, vector<T> v) {
    for(T e: v) {
        out << e << " ";
    }
    return out;
}

vector<int> badchar(string pat) {
	vector<int> bc(256, -1);
	for(int i = 0; i < pat.size(); ++i) {
		int c = pat[i];
		bc[c] = i;
	}
	return bc;
}

vector<int> goodsuffix(string pat) {
	int m = pat.size();
	int border = brd(pat).at(m);
	vector<int> gs(m + 1, border);
	string revpat = pat;
	reverse(revpat.begin(), revpat.end());
	vector<int> revbrd = brd(revpat);
	for(int l = 1; l <= m; ++l) {
		int j = m - 1 - revbrd[l];
		gs[j + 1] = max(gs[j + 1], m - l + revbrd[l]);
	}
	return gs;
}

vector<int> boyermoore(string txt, string pat, vector<int> bc, vector<int> gs) {
	int n = txt.size(),
		m = pat.size();
	vector<int> occ;
	int i = 0;
	while(i <= n - m) {
		int j = m - 1;
		while(j >= 0 && txt[i + j] == pat[j]) {
			j -= 1;
		}
		if(j == -1) {
			occ.push_back(i);
			i += m - gs[0];
		}
		else {
			i += max(j - bc[txt[i + j]], m - gs[j + 1]);
		}
	}
	return occ;
}

int main() {
    string txt, pat;
    cin >> txt >> pat;
    cout << kmp(txt, pat, brd(pat)) << endl; 
    return 0;
}


