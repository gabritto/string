#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int uint;
const int word_size = 32;

struct bitvector {
	int size;
	vector<uint> bitvec;

	bitvector(int n) : size(n), arr((n + word_size - 1) / word_size, 0) {}
	
	int size() {
		return size;
	}

	void set(int pos) {
		if(pos < size && pos > 0) {
			int vector_idx = pos / word_size;
			int bit_idx = pos - vector_idx * word_size;
			bitvec[vector_idx] |= 1U << bit_idx;
		}
		else {
			cerr << "pos out of bounds" << endl;
		}
	}

	void reset(int pos) {
		if(pos < size && pos > 0) {
			int vector_idx = pos / word_size;
			int bit_idx = pos - vector_idx * word_size;
			bitvec[vector_idx] &= ~(1U << bit_idx);
		}
		else {
			cerr << "pos out of bounds" << endl;
		}
	}

	int getbit(int pos) {
		if(pos < size && pos > 0) {
			int vector_idx = pos / word_size;
			int bit_idx = pos - vector_idx * word_size;
			return (bitvec[vector_idx] >> bit_idx) & 1;
		}
		else {
			cerr << "pos out of bounds" << endl;
		}
	}

	bitvector& operator |=(const bitvector &q) {
		for(int i = 0; i < int(bitvec.size()) && i < int(q.bitvec.size()); ++i) {
			bitvec[i] |= q.bitvec[i];
		}
		return *this;
	}

	bitvector& operator <<(int n) {
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

}


int main() {
	
	return 0;
}
