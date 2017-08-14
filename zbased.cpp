#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

const int alphabetSize = 256;

template <class T>
void print(std::vector<T> v) {
	for(T e: v) {
		std::cout << e << " ";
	}
	std::cout << std::endl;
}

// Z-value of position 0 is set to be 0
std::vector<int> GetZValues(std::string pat) {
	std::vector<int> z(pat.size(), 0);
	int l = 0, r = 0;
	for(int i = 1; i < pat.size(); ++i) {
		if(i > r) {
			while(i + z[i] < pat.size() && pat[i + z[i]] == pat[z[i]]) {
				z[i] += 1;
			}
			l = i;
			r = i + z[i] - 1;
		}
		else {
			z[i] = std::min(z[i - l], r - i);
			while(i + z[i] < pat.size() && pat[i + z[i]] == pat[z[i]]) {
				z[i] += 1;
			}
			if(i + z[i] - 1 > r) {
				r = i + z[i] - 1;
				l = i;
			}
		}
	}
	return z;
}

// Assumes ASCII alphabet.
// R[x][i] is the largest position j less than i such that P[j] = x (where P is the input pattern).
std::vector<std::vector<int>> GetBadCharTable(std::string pat) {
	std::vector<std::vector<int>> R(alphabetSize, std::vector<int>(pat.size(), -1));
	for(int i = 0; i < pat.size() - 1; ++i) {
		int ch = int(pat[i]);
		R[ch][i + 1] = i;
	}
	for(int j = 0; j < alphabetSize; ++j) {
		for(int i = 1; i < pat.size(); ++i) {
			R[j][i] = std::max(R[j][i], R[j][i - 1]);
		}
	}
	return R;
} 

// First element is vector L', where L'[i] is the largest position smaller than
// n = |P| (where P is the input pattern) such that string P[i .. n] matches a
// suffix of P[0 .. L'[i]] and the character preceding that suffix
// (if it exists) is not equal to P[i - 1].
// Second element is vector l' where l'[i] is the lenght of the largest suffix
// of P[i .. n] that is also a prefix of P.
std::pair<std::vector<int>, std::vector<int>> GetGoodSuffixTable(std::string pat) {
	std::string reverse_pat = pat;
	std::reverse(reverse_pat.begin(), reverse_pat.end());
	std::vector<int> n_value = GetZValues(reverse_pat);
	reverse(n_value.begin(), n_value.end());
	std::vector<int> l_value(pat.size() + 1, -1);
	for(int j = 0; j < pat.size() - 1; ++j) {
		int i = pat.size() - n_value[j];
		l_value[i] = j;
	}
	print(n_value);
	print(l_value);
	std::vector<int> l_prime_value(pat.size() + 1, 0);
	for(int j = pat.size() - 1; j >= 0; --j) {
		l_prime_value[j] = l_prime_value[j + 1];
		int i = pat.size() - j;
		if(n_value[i - 1] == i) {
			l_prime_value[j] = i;
		}
	}
	print(l_prime_value);
	return std::make_pair(l_value, l_prime_value);
}

int main() {
	std::string s;
	std::cin >> s;
	GetGoodSuffixTable(s);
	return 0;
}



