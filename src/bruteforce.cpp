#include <string>
#include <vector>

using namespace std;

namespace bruteforce {
	static vector<string> pats;
	void build(const vector<string> &_pats) {
		pats = _pats;
	}
	int search(const char *txt) {
		int count = 0;
		for(int k = 0; k < (int) pats.size(); ++k) {
			int m = (int) pats[k].size();
			for(int i = 0; txt[i] != '\0'; ++i) {
				int j = 0;
				int l = i;
				while(j < m && txt[i] != '\0' && pats[k][j] == txt[l]) {
					++j;
					++l;
				}
				count += j == m;
			}
		}
		return count;
	}
}