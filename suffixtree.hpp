#ifndef SUFFIX_TREE_HPP
#define SUFFIX_TREE_HPP

#include <bits/stdc++.h>

using namespace std;

const int inf = 1e9;

class Text {
public:
	Text();
	Text(const char *str);
	const char *str;
	int str_len;
	int hsh[256];
	int alpha_size;
private:
	void buildHash();
};


class SuffixTree {
public:
	SuffixTree(const char *str);
	~SuffixTree();
private:
	struct Node {
		int l = inf, r = inf;
		Node **child = NULL;
		Node *suffix_link = NULL;
		Node();
		Node(int l, int r, int alpha_size);
		~Node();
	};
	Text txt;
	Node *buffer;
	Node *ptr;
	Node* newNode(int l, int r);
	pair<Node*, pair<int, int>> canonise(Node *u, int l, int r);
	pair<Node*, bool> testAndSplit(Node *u, int l, int r, int i);
	pair<Node*, pair<int, int>> update(Node *u, int l, int r, int i);
	void buildSuffixTree();
};



#endif