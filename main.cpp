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
	char s[2 * 1000000 + 10];
	memset(s, 0, sizeof(s));

	char *ptr = s;

	for(int i = 0; i < 1000000; ++i) {
		ptr = strcat(ptr, "61");
	}

	uint32_t* H = sha256(s);

	for(int i = 0; i < 8; ++i) {
		printf("%08x ", H[i]);
	}

	free(H);
	return 0;
}

