#include <bits/stdc++.h>

#include "duonghash.hpp"

using namespace std;
using namespace duonghash;

void display(unsigned long long a) {
	for(int i = 32; i--;) {
		cout << (a >> i & 1);
	}
	cout << '\n';
}

int main() {
	uint32_t* H = binary_sha256("011000010110001001100011");

	for(int i = 0; i < 8; ++i) {
		cout << hex << H[i] << ' ';
	}

	free(H);
	return 0;
}

