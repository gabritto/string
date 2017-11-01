#include "suffixtree.hpp"

using namespace std;

Text::Text() {}
Text::Text(const char *str) {
		this->str = str;
		str_len = (int) strlen(str) + 1;
		buildHash();
	}


void Text::buildHash() {
	memset(hsh, 0, sizeof hsh);
	alpha_size = 1;
	for(int i = 0; i < str_len; ++i) {
		if(hsh[(unsigned char) str[i]] == 0) {
			hsh[(unsigned char) str[i]] = alpha_size++;
		}
	}
}


SuffixTree::SuffixTree(const char *str) {
	this->txt = Text(str);
	this->matches = vector<int>(2 * txt.str_len);
	this->buffer = vector<Node>(2 * txt.str_len);
	this->root = build();
}


SuffixTree::Node::Node() {}
SuffixTree::Node::Node(int l, int r, int alpha_size) {
	this->l = l;
	this->r = r;
	this->child = vector<Node*>(alpha_size, NULL);
}



SuffixTree::Node* SuffixTree::newNode(int l, int r) {
	Node *ret = &buffer[ptr++];
	*ret = Node(l, r, txt.alpha_size);
	return ret;
}
pair<SuffixTree::Node*, pair<int, int>> SuffixTree::canonise(SuffixTree::Node *u, int l, int r) {
	//printf("canonising (%d, (%d, %d))\n", u - &buffer[0], l, r);
	while(l < r) {
		Node *v = u->child[txt.hsh[(unsigned char) txt.str[l]]];
		if(v->r - v->l <= r - l) {
			l += v->r - v->l;
			u = v;
		}
		else {
			break;
		}
	}
	//printf("returning (%d, (%d, %d))\n", u - &buffer[0], l, r);
	return {u, {l, r}};
}

pair<SuffixTree::Node*, bool> SuffixTree::testAndSplit(SuffixTree::Node *u, int l, int r, int i) {
	//printf("spliting (%d, (%d, %d))\n", u - &buffer[0], l, r);
	if(l == r) {
		//printf("returning2 %d, %d\n", u - &buffer[0], u->child[txt.hsh[(unsigned char) txt.str[i]]] != NULL);
		return {u, u->child[txt.hsh[(unsigned char) txt.str[i]]] != NULL};
	}
	else {
		Node *v = u->child[txt.hsh[(unsigned char) txt.str[l]]];
		if(txt.str[v->l + r - l] == txt.str[i]) {
			//printf("returning1 %d, %d\n", u - &buffer[0], true);

			return {u, true};
		}
		else {
			Node *w = newNode(v->l, v->l + r - l);
			v->l += r - l;
			u->child[txt.hsh[(unsigned char) txt.str[l]]] = w;
			w->child[txt.hsh[(unsigned char) txt.str[v->l]]] = v;
			//printf("returning %d, %d\n", w - &buffer[0], false);

			return {w, false};
		}
	}
}

pair<SuffixTree::Node*, pair<int, int>> SuffixTree::update(SuffixTree::Node *u, int l, int r, int i) {
	Node *prev_w = NULL;
	bool is_term;
	Node *w;
	tie(w, is_term) = testAndSplit(u, l, r, i);
	//printf("%d, %c, %d, %d\n", i, txt.str[i], l, r);
	while(!is_term) {
		//printf("%d\n", is_term);
		Node *leaf = newNode(i, inf);
		w->child[txt.hsh[(unsigned char) txt.str[i]]] = leaf;
		//printf("creating child %d em %d\n", txt.hsh[(unsigned char) txt.str[i]], w - &buffer[0]);
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

SuffixTree::Node* SuffixTree::build() {
	Node *ground = newNode(-1, -1);
	Node *root = newNode(-1, 0);
	for(int i = 0; i < txt.alpha_size; ++i) {
		ground->child[i] = root;
	}
	root->suffix_link = ground;
	Node *u = root;
	int l = 0, r = 0;
	for(int i = 0; i < txt.str_len; ++i) {
		//printf("\n\n");
		//printf("brd=(%d, (%d, %d))\n", u - &buffer[0], l, r);
		pair<int, int> range;
		tie(u, range) = update(u, l, r, i);
		tie(l, r) = range;
		//printf("term=(%d, (%d, %d))\n", u - &buffer[0], l, r);
		tie(u, range) = canonise(u, l, r + 1);
		tie(l, r) = range;
		//printf("i = %d\n", i);
		//this->print(1, 0);
	}

	//printf("FIM\n");
	buildMatches(root);
	return root;
}

int SuffixTree::buildMatches(Node *u) {
	if(u == NULL) {
		return 0;
	}
	else {
		matches[u - &buffer[0]] = 1;
		for(int i = 0; i < txt.alpha_size; ++i) {
			if(u->child[i] != NULL) {
				matches[u - &buffer[0]] += buildMatches(u->child[i]);
				//printf("[id=%d, filho=%d, matches=%d]\n", u - &buffer[0], u->child[i] - &buffer[0], matches[u - &buffer[0]]);
			}
		}
		return matches[u - &buffer[0]];
	}
}

int SuffixTree::search(const char *pat) {
	return search(root, pat);
}

int SuffixTree::search(Node *u,  const char *pat) {
	if(*pat == '\0') {
		//printf("aqui2 %d\n", u - &buffer[0]);

		return matches[u - &buffer[0]];
	}
	else {
		Node *v = u->child[txt.hsh[*pat]];
		if(v == NULL) {
			return 0;
		}
		int i = v->l;
		//printf("aqui3 %d\n", txt.str[i]);
		while(i < v->r && *pat != '\0') {
			//printf("%c %c\n", txt.str[i], *pat);
			if(txt.str[i] != *pat) {
				return 0;
			}
			else {
				++i;
				++pat;
			}
		}
		return search(v, pat);
	}
}



void SuffixTree::print(int v, int level = 0) {
	Node *u = &buffer[v];
	if(u != NULL) {
		printf("%s[id=%d l=%d r=%d slink=%d matches=%d]\n", string(2*level, ' ').c_str(), u - &buffer[0], u->l, u->r, u->suffix_link == NULL ? -1 : u->suffix_link - &buffer[0], matches[u - &buffer[0]]);
		for(int i = 0; i < txt.alpha_size; ++i) {
			if(u->child[i] != NULL) {
				print(u->child[i] - &buffer[0], level + 1);
			}
		}
	}
}
int main() {
	char str[] = "mississipi";	
	SuffixTree st(str);
	//st.print(1);
	return 0;
}