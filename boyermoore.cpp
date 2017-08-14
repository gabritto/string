#include <iostream>
#include <string>

//Z-value of position 0 is set to be 0
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

std::vector<int> 

int main() {
	return 0;
}
