#include "suffixtree.hpp"

using namespace std;


Text::Text() {}
Text::Text(const char *str) {
		this->str = str;
		str_len = (int) strlen(str);
		buildHash();
	}


void Text::buildHash() {
	memset(hsh, -1, sizeof hsh);
	alpha_size = 0;
	for(int i = 0; i < str_len; ++i) {
		if(hsh[(unsigned char) str[i]] == -1) {
			hsh[(unsigned char) str[i]] = alpha_size++;
		}
	}
}


SuffixTree::SuffixTree(const char *str) {
	this->txt = Text(str);
	this->ptr = this->buffer = new Node[2 * txt.str_len];
}
SuffixTree::~SuffixTree() {
	delete[] buffer;
}

SuffixTree::Node::Node() {}
SuffixTree::Node::Node(int l, int r, int alpha_size) {
	this->l = l;
	this->r = r;
	this->child = new Node*[alpha_size];
	for(int i = 0; i < alpha_size; ++i) {
		this->child[i] = NULL;
	}
}
SuffixTree::Node::~Node() {
	delete[] child;
}


SuffixTree::Node* SuffixTree::newNode(int l, int r) {
	Node *ret = ptr++;
	*ret = Node(l, r, txt.alpha_size);
	return ret;
}
pair<SuffixTree::Node*, pair<int, int>> SuffixTree::canonise(SuffixTree::Node *u, int l, int r) {
	while(l < r) {
		Node *v = u->child[(unsigned char) txt.str[l]];
		if(v->r - v->l <= r - l) {
			l += v->r - v->l;
			u = v;
		}
	}
	return {u, {l, r}};
}

pair<SuffixTree::Node*, bool> SuffixTree::testAndSplit(SuffixTree::Node *u, int l, int r, int i) {
	if(l == r) {
		return {u, u->child[(unsigned char) txt.str[i]] != NULL};
	}
	else {
		Node *v = u->child[(unsigned char) txt.str[l]];
		if(txt.str[v->l] + r - l == txt.str[i]) {
			return {u, true};
		}
		else {
			Node *w = newNode(v->l, v->l + r - l);
			v->l += r - l;
			u->child[(unsigned char) txt.str[l]] = w;
			w->child[(unsigned char) txt.str[v->l]] = v;
			return {w, false};
		}
	}
}

pair<SuffixTree::Node*, pair<int, int>> SuffixTree::update(SuffixTree::Node *u, int l, int r, int i) {
	Node *prev_w = NULL;
	bool is_term;
	Node *w;
	tie(w, is_term) = testAndSplit(u, l, r, i);
	while(is_term) {
		Node *leaf = newNode(i, inf);
		w->child[(unsigned char) txt.str[i]] = leaf;
		if(prev_w != NULL) {
			prev_w->suffix_link = w;
		}
		prev_w = w;
		pair<int, int> range;
		tie(u, range) = canonise(u->suffix_link, l, r);
		tie(l, r) = range;
		tie(w, is_term) = testAndSplit(u, l, r, i);
	}
	if(prev_w != NULL) {
		prev_w->suffix_link = w;
	}

	return {u, {l, r}};
}

void SuffixTree::buildSuffixTree() {
	Node *ground = newNode(-1, -1);
	Node *root = newNode(-1, 0);
	for(int i = 0; i < txt.alpha_size; ++i) {
		ground->child[i] = root;
	}
	root->suffix_link = ground;
	Node *u = root;
	int l = 0, r = 0;
	for(int i = 0; i < txt.str_len; ++i) {
		pair<int, int> range;
		tie(u, range) = update(u, l, r, i);
		tie(l, r) = range;
		tie(u, range) = canonise(u, l, r);
		tie(l, r) = range;
	}
}

int main() {
	char str[] = "MISSISSIPPI$";	
	SuffixTree st(str);

	return 0;
}