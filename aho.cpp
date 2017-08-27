#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

const int sigma = 256;

map<pair<int, int>, int> aho(string pat) {
	map<pair<int, int>, int> fsm;
	int m = pat.size();
	if(m == 0)
		return fsm;
	for(int i = 0; i < sigma; ++i) {
		fsm[make_pair(0, i)] = 0;
	}
	fsm[make_pair(0, pat[0])] = 1;
	int brd = 0;
	for(int i = 1; i <= m; ++i) {
		cout << "brd " << i << ": " << brd << endl; 		
		for(int s = 0; s < sigma; ++s) {
			fsm[make_pair(i, s)] = fsm[make_pair(brd, s)];
		}
		if(i < m) {
			fsm[make_pair(i, pat[i])] = i + 1;
			brd = fsm[make_pair(brd, pat[i])];
		}
	}
	return fsm;
}

vector<int> corasick(string txt, map<pair<int, int>, int> fsm, int m) {
	int n = txt.size();
	vector<int> occ;
	int st = 0;
	for(int i = 0; i < n; ++i) {
		st = fsm[make_pair(st, txt[i])];
		if(st == m)
			occ.push_back(i);
	}
	return occ;
}

int main() {
	string s;
	while(cin >> s && s != "stop") {
		aho(s);	
	}
	return 0;
}
