#include <iostream>
#include "z.hpp"

int main() {
	std::string s;
	std::cin >> s;
	std::vector<int> z_value = GetZValues(s);
	for(int z: z_value) {
		std::cout << z << " ";
	}
	std::cout << std::endl;
	return 0;
}
