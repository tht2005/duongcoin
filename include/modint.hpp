#ifndef MODINT_HPP
#define MODINT_HPP

#include <cstdint>

template<class T>
T addmod(T a, T b, const T& md) {
	a += b;
	if(a >= md) {
		a -= md;
	}
	if(a < 0) {
		a += md;
	}
	return a;
}

template<class T>
T binmul(T a, T b, const T& md) {
	T res = 0;
	for(; b > 0; b >>= 1) {
		if(b & 1) {
			res = addmod<T>(res, a, md);
		}
		a = addmod<T>(a, a, md);
	}
	return res;
}

template<class T>
T binpow(T a, uint64_t n, const T& md) {
	a %= md;
	T res = 1;
	for(; n > 0; n >>= 1) {
		if(n & 1) {
			res = binmul<T>(res, a, md);
		}
		a = binmul<T>(a, a, md);
	}
	return res;
}

#endif
