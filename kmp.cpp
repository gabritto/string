#include <bits/stdc++.h>

vector<int> brd(string pat) {
	int m = pat.size();
	vector<int> nxt(m + 1, 0);
	int i = 1,
		j = 0;
	while(i + j < m) {
		while(i + j < m && pat[i + j] == pat[j]) {
			j += 1;
			nxt[i + j] = j;
		}
		i += max(1, j - nxt[j]);
		j = nxt[j];
	}
	return nxt;
}

vector<int> kmp(string txt, string pat) {
	int n = txt.size(),
		m = pat.size();
	vector<int> occ;
	vector<int> nxt = brd(pat);
	int i = 0,
		j = 0;
	while(i <= n - m) {
		while(j < m && txt[i + j] == pat[j]) {
			j += 1;
		}
		if(j == m) {
			occ.push_back(i);
		}
		i += max(1, j - nxt[j]);
		j = nxt[j];
	}
	return occ;
}

template <class T>
ostream & operator<<(ostream &outstream, vector<T> v) {
	for(auto i: v) {
		outstream << i << " ";
	}
	return outstream;
}

int main() {
	string txt, pat;
	cin >> txt >> pat;
	cout << kmp(txt, pat) << endl;	
	return 0;
}
