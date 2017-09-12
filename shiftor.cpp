#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;
const int word_size = 32;
const uint one = 1U;

struct bitvector {
	int size; //number of bits in the bitvector
	vector<uint> bitvec;

	bitvector(int n, uint b = 0) : size(n), bitvec((n + word_size - 1) / word_size, b) {}
	
	void set(int pos) {
		if(pos < size && pos >= 0) {
			int vector_idx = pos / word_size;
			int bit_idx = pos % word_size;
			bitvec[vector_idx] |= one << bit_idx;
		}
		else {
			cerr << "pos out of bounds" << endl;
		}
	}

	void reset(int pos) {
		if(pos < size && pos >= 0) {
			int vector_idx = pos / word_size;
			int bit_idx = pos % word_size;
			bitvec[vector_idx] &= ~(one << bit_idx);
		}
		else {
			cerr << "pos out of bounds" << endl;
		}
	}

	int getbit(int pos) {
		if(pos < size && pos >= 0) {
			int vector_idx = pos / word_size;
			int bit_idx = pos % word_size;
			return (bitvec[vector_idx] >> bit_idx) & one;
		}
		else {
			cerr << "pos out of bounds" << endl;
			return -1;
		}
	}

	bitvector& operator |=(const bitvector &q) {
		for(int i = 0; i < int(bitvec.size()) && i < int(q.bitvec.size()); ++i) {
			bitvec[i] |= q.bitvec[i];
		}
		return *this;
	}

	bitvector& operator <<=(int n) {
		for(int i = size - 1; i >= 0; --i) {
			int j = i - n;
			if(j < 0) {
				reset(i);
			}
			else {
				int b = getbit(j);
				if(b == 1)
					set(j);
				else
					reset(j);
			}
		}
		return *this;
	}

	bitvector& operator ++() {
		for(int i = bitvec.size() - 1; i > 0; --i) {
			bitvec[i] <<= 1;
			bitvec[i] |= (bitvec[i - 1] >> (word_size - 1)) & one;
		}
		if(bitvec.size() > 0) {
			bitvec[0] <<= 1;
		}
		return *this;
	}
	
	void print() {
		for(int i = size - 1; i >= 0; --i) {
			printf("%2d ", i);
		}
		cout << endl;
		for(int i = size - 1; i >= 0; --i) {
			printf("%2d ", getbit(i));
		}
		cout << endl;
	}
};

const int sigma = 256;

vector<bitvector> char_mask(string pat) {
	int m = pat.size();
	vector<bitvector> C(256, bitvector(m, ~0));
	for(int i = 0; i < m; ++i) {
		C[pat[i]].reset(i);
	}
	return C;
}

vector<int> shift_or(string txt, string pat) {
	int n = txt.size(), m = pat.size();
	bitvector S(m, ~(0));
	vector<bitvector> C = char_mask(pat); 
	vector<int> occ;
	for(int i = 0; i < n; ++i) {
		++S |= C[txt[i]];
		if(S.getbit(m - 1) == 0) {
			occ.push_back(i - m + 1);
		} 
	}
	return occ;
}

int main() {
	string txt, pat;
	cin >> txt >> pat;
	vector<int> occ = shift_or(txt, pat);
	for(auto p: occ)
		cout << p << " " << endl;
	return 0;
}





