#include "util.hpp"
#include "ukkonen.hpp"

#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

namespace ukkonen {

static vector<vector<int>> trie;
static vector<int> node_id;
static vector<vector<int>> fsm;
static vector<int> alphabet_hash;
static vector<bool> is_final;
static int alphabet_size;
static int node_count = 0;
static int err;

static vector<int> next_column(const vector<int> &col, const string &pat, int ch) {
	int m = col.size();
	vector<int> newcol(m, 0);
	for(int i = 1; i < m; ++i) {
		int phi = 0;
		if(ch != alphabet_hash[(unsigned char) pat[i - 1]]) {
			phi = 1;
		}
		newcol[i] = max(err + 1, min(newcol[i - 1] + 1, min(col[i] + 1, col[i - 1] + phi)));
	}
	return newcol;
}

static pair<int, bool> insert(const vector<int> &col) {
	int cur = 0;
	int i = 0;
	int m = col.size();
	int d = 1;
	while(i < m && trie[cur][d] != -1) {
		cur = trie[cur][d];
		++i;
		if(i < m) {
			d = 1 + col[i] - col[i - 1];
		}
	}
	
	while(i < m - 1) {
		int nxt = trie.size();
		trie.push_back(vector<int>(3, -1));
		node_id.push_back(-1);
		trie[cur][d] = nxt;
		cur = nxt;
		++i;
		d = 1 + col[i] - col[i - 1];
	}
	bool is_new = false;

	if(i == m - 1) {
		int nxt = trie.size();
		trie.push_back(vector<int>(3, -1));
		node_id.push_back(node_count++);
		trie[cur][d] = nxt;
		cur = nxt;
		is_new = true;
		is_final.push_back(col[m - 1] <= err);
	}
	
	return {node_id[cur], is_new};
}

void build(const string &pat, int r) {
	tie(alphabet_hash, alphabet_size) = getAlphabet(pat);
	int m = pat.size();
	err = r;
	vector<int> col(m + 1, 0);
	fsm.push_back(vector<int>(alphabet_size, 0));
	int col_id;
	bool is_new;
	tie(col_id, is_new) = insert(col);
	queue<pair<vector<int>, int>> Q;
	Q.push({col, col_id});
	while(!Q.empty()) {
		tie(col, col_id) = Q.front();
		Q.pop();
		for(int ch = 0; ch < alphabet_size; ++ch) {
			vector<int> newcol = next_column(col, pat, ch);
			bool is_new;
			int newcol_id;
			tie(newcol_id, is_new) = insert(newcol);
			if(is_new) {
				Q.push({newcol, newcol_id});
			}
			fsm[col_id][ch] = newcol_id;
		}
	}
}

int search(const string &txt) {
	int cur = 0;
	int occ = 0;
	for(unsigned char ch : txt) {
		int p = alphabet_hash[ch];
		cur = fsm[cur][p];
		if(is_final[cur]) {
			++occ;
		}
	}
	return occ;
}

} //namespace ukkonen
