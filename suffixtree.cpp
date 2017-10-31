#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

class SuffixTree {
public:

private:
	struct Node {
		int l, r;
		Node* child[alpha_size];
		Node* suffix_link;
		Node() {}
		Node(int l, int r) {
			this->l = l;
			this->r = r;
			memset(child, -1, sizeof child);
			suffix_link = NULL;
		}
	};
	const char *str;
	Node *buffer; // = new Node[strlen(str)]
	Node *ptr;
	Node* newNode(int l, int r) {
		Node *ret = ptr++;
		*ret = Node(l, r);
		return ret;
	}
	pair<Node*, pair<int, int>> canonise(Node *u, int l, int r) {
		while(l < r) {
			Node *v = u->child[str[l]];
			if(v->r - v->l <= r - l) {
				l += v.r - v.l;
				u = v;
			}
		}
		return {u, {l, r}};
	}

	pair<Node*, bool> testAndSplit(Node *u, int l, int r, int i) {
		if(l == r) {
			return {u, u->child[str[i]] != -1};
		}
		else {
			v = u->child[str[l]];
			if(str[v->l] + r - l == str[i]) {
				return {true, u};
			}
			else {
				Node *w = newNode(v->l, v->l + r - l);
				v->l += r - l;
				u.child[str[l]] = w;
				w.child[str[v->l]] = v;
				return {false, w};
			}
		}
	}

	pair<Node*, pair<int, int>> update(Node *u, int l, int r, int i) {
		Node *prev_w = NULL;
		bool is_term;
		Node *w;
		tie(is_term, w) = testAndSplit(u, l, r, i);
		while(is_term) {
			Node *leaf = newNode(i, inf);
			w.child[str[i]] = leaf;
			if(prev_w != NULL) {
				prev_w->suffix_link = w;
			}
			prev_w = w;
			tie(u, tie(l, r)) = canonise(u->suffix_link, l, r);
			tie(is_term, w) = testAndSplit(u, l, r, i);
		}
		if(prev_w != NULL) {
			prev_w->suffix_link = w;
		}

		return {u, {l, r}};
	}

	void buildSuffixTree() {
		Node *ground = newNode(-1, -1);
		Node *root = newNode(-1, 0);
		for(int i = 0; i < alpha_size; ++i) {
			ground->child[i] = root;
		}
		root->suffix_link = ground;
		Node *u = root;
		int l = 0, r = 0;
		for(int i = 0; str[i] != '\0'; ++i) {
			tie(u, tie(l, r)) = update(u, l, r, i);
			tie(u, tie(l, r)) = canonise(u, l, r);
		}
	}
};


int main() {
	


	return 0;
}